#include "CodeGenerator.h"
#include <cassert>
#include <iostream>
#include <random>

#ifdef DEBUG_TRANSLATOR_TRACER
#include <experimental/source_location>
#define translator() std::experimental::source_location::current(), translator()
#endif

namespace oneCC::CodeGenerator::Aarch32 {

CodeGeneratorAarch32::CodeGeneratorAarch32()
    : m_translator()
    , m_varManager()
    , m_registerManager(*this)
    , m_outputManager(*this)
    , m_storage()
    , m_transactionManager(*this)
{
}

int CodeGeneratorAarch32::processTree(AST::Node* program)
{
    visitNode(program);
    output().print();
    return 0;
}

void CodeGeneratorAarch32::visitNode(AST::BinaryOperationNode* node)
{
    if (node->operation() == Lexer::TokenType::Plus) {
        genBinaryMathOperation(node, [&](Register& res, Register& l, Register& r) {
            output().add(translator().ADD_reg(res, l, r));
        });
    } else if (node->operation() == Lexer::TokenType::Minus) {
        genBinaryMathOperation(node, [&](Register& res, Register& l, Register& r) {
            output().add(translator().SUB_reg(res, l, r));
        });
    } else if (node->operation() == Lexer::TokenType::Assign) {
        genBinaryAssign(node);
    } else if (node->operation() == Lexer::TokenType::Equal) {
        int rnd = rand() % 90 + 10;
        std::string trueLabel("Lbl" + std::to_string(rnd));

        if (m_storage[OP_INVERSED]) {
            genBinaryCmpOperation(node, [&](Register& l, Register& r) {
                output().add(translator().CMP(l, r));
                output().add(translator().BNE(0, trueLabel));
                m_storage[OP_SAVED_PLACE_FALSE_BRANCH] = output().saveSpot();
            });
            m_transactionManager.active().setFalseBranchInstrId(output().addLabel(trueLabel));
        } else {
            genBinaryCmpOperation(node, [&](Register& l, Register& r) {
                output().add(translator().CMP(l, r));
                output().add(translator().BEQ(0, trueLabel));
                m_storage[OP_SAVED_PLACE_FALSE_BRANCH] = output().saveSpot();
            });
            m_transactionManager.active().setTrueBranchInstrId(output().addLabel(trueLabel));
        }
    }
}

void CodeGeneratorAarch32::visitNode(AST::TernaryOperationNode* node)
{
    if (m_storage[FUNC_PROCESSING] == 1) {
        if (node->rightChild()) {
            auto* identifierNode = reinterpret_cast<AST::IdentifierNode*>(node->middleChild());

            m_transactionManager.create();
            visitNode(node->rightChild());
            Register& reg = m_transactionManager.active().resultRegister();
            m_transactionManager.end();

            int varId = m_varManager.getId(identifierNode->value());
            output().add(translator().STR_imm_offset(reg, Register::FP(), -m_varManager.getOffset(varId)));
        }
    } else {
        // We are no in func, seems a global
    }
}

void CodeGeneratorAarch32::visitNode(AST::BlockStatementNode* blk)
{
    for (auto* node : blk->statements()) {
        visitNode(node);
    }
}
void CodeGeneratorAarch32::visitNode(AST::ReturnStatementNode* ret)
{
    // TODO: Allow to set preferable register
    m_transactionManager.create();
    visitNode(ret->returnedExpression());
    Register& resultRegister = m_transactionManager.active().resultRegister();
    m_transactionManager.end();

    if (Register::R0() != resultRegister) {
        if (m_registerManager.replace(Register::R0(), RegisterData::Tmp()) == 0) {
            output().add(translator().MOV_reg(Register::R0(), resultRegister));
        }
    }
}

void CodeGeneratorAarch32::visitNode(AST::BooleanSnakeNode* node)
{
    int rnd = rand() % 90 + 10;
    std::string exprLabel("Expr" + std::to_string(rnd));
    std::string trueLabel("True" + std::to_string(rnd));
    std::string falseLabel("Fals" + std::to_string(rnd));
    int outNode = output().activeNode().id();
    int expr = output().addLabel(exprLabel);
    int trueLabelId = 0;
    int falseLabelId = 0;

    if (node->operation() == Lexer::TokenType::And) {
        for (auto i : node->nodes()) {
            m_transactionManager.create();

            // Mark operations to be generated as inversed. For example > will be considered to be a <= operation.
            m_storage[OP_INVERSED] = 1;

            visitNode(i);

            // Since we have a sequnce of calls, we need to countinue in true branch, if it was set.
            int trueInstruction = m_transactionManager.active().trueBranchInstrId();
            if (trueInstruction != -1) {
                output().setOutputNode(trueInstruction);
            }

            // Because we are in And, all false instructions are just jump to the false label.
            int falseInstruction = m_transactionManager.active().falseBranchInstrId();
            output().add(falseInstruction, translator().BL(0, falseLabel));

            m_transactionManager.end();
        }

        trueLabelId = output().addLabel(trueLabel);
        output().setOutputNode(outNode);
        falseLabelId = output().addLabel(falseLabel);
    }

    if (node->operation() == Lexer::TokenType::Or) {
        for (auto i : node->nodes()) {
            m_transactionManager.create();

            m_storage[OP_INVERSED] = 0;
            visitNode(i);

            int flaseInstruction = m_transactionManager.active().falseBranchInstrId();
            if (flaseInstruction != -1) {
                output().setOutputNode(flaseInstruction);
            }

            // Because we are in Or, all true instructions are just jump to the true label.
            int trueInstruction = m_transactionManager.active().trueBranchInstrId();
            output().add(trueInstruction, translator().BL(0, trueLabel));

            m_transactionManager.end();
        }
        output().add(translator().BL(0, falseLabel));
        trueLabelId = output().addLabel(trueLabel);
        output().setOutputNode(outNode);
        falseLabelId = output().addLabel(falseLabel);
    }

    m_transactionManager.active().setFalseBranchInstrId(falseLabelId);
    m_transactionManager.active().setTrueBranchInstrId(trueLabelId);
}

void CodeGeneratorAarch32::visitNode(AST::IfStatementNode* node)
{
    int rnd = rand() % 90 + 10;
    std::string exitLabel("EXTF" + std::to_string(rnd)); // Exit from 'if', if we have else
    m_transactionManager.create();
    visitNode(node->expression());

    addFalseBranch(node->expression());

    // After expression we think we got trueLabel and falseLabel (aka if and else);
    int outNode = output().activeNode().id();

    int trueInstruction = m_transactionManager.active().trueBranchInstrId();
    if (trueInstruction != -1 && node->trueStatement()) {
        output().setOutputNode(trueInstruction);
        visitNode(node->trueStatement());
        if (node->falseStatement()) {
            output().add(translator().BL(0, exitLabel));
        }
    }

    int falseInstruction = m_transactionManager.active().falseBranchInstrId();
    if (falseInstruction != -1 && node->falseStatement()) {
        output().setOutputNode(falseInstruction);
        visitNode(node->falseStatement());
    }

    output().setOutputNode(outNode);
    if (node->falseStatement()) {
        output().addLabel(exitLabel);
    }
    m_transactionManager.end();
}

void CodeGeneratorAarch32::visitNode(AST::WhileStatementNode* a) {}

void CodeGeneratorAarch32::visitNode(AST::FunctionNode* func)
{
    m_registerManager.resetUsedRegisters();
    m_storage[FUNC_PROCESSING] = 1;
    m_storage[FUNC_MAIN_LABEL] = output().addLabel(func->identifier()->value());
    initStackFrame(func);

    // Saving args to stack
    for (int argId = 0; argId < func->arguments().size(); argId++) {
        if (argId <= 4) {
            // in register
            // We use this hack, since args are in r0-r4 which has RegisterAlias = 0-4;
            Register& reg = Register::RegisterList()[argId];
            int varId = m_varManager.getId(func->arguments()[argId]->identifier()->value());

            assert((m_registerManager.replace(reg, RegisterData(DataVariable, varId)) == 0));
            output().add(translator().STR_imm_offset(reg, Register::FP(), -m_varManager.getOffset(varId)));
        }
    }

    output().add(translator().addLabel(""));

    visitNode(func->statement());

    output().add(translator().addLabel(""));
    restoreStackFrame(func);
    output().add(translator().addLabel(""));
    m_storage[FUNC_PROCESSING] = 0;
}

void CodeGeneratorAarch32::visitNode(AST::FunctionCallNode* node)
{
    bool wasR0busy = false;
    m_transactionManager.create();
    for (int argId = 0; argId < node->arguments().size(); argId++) {
        if (argId <= 4) {
            // in register
            // We use this hack, since args are in r0-r4 which has RegisterAlias = 0-4;

            Register& putTo = Register::RegisterList()[argId];
            if (!m_registerManager.canUse(putTo)) {
                if (argId == 0) {
                    wasR0busy = true;
                }
                m_registerManager.resolveForbiddenRegister(putTo);
            }
            assert(m_registerManager.canUse(putTo));

            visitNode(node->arguments()[argId]);
            Register& reg = m_transactionManager.active().resultRegister();

            if (reg != putTo) {
                if (m_registerManager.replace(putTo, reg.data()) == 0) {
                    output().add(translator().MOV_reg(putTo, reg));
                }
            }

            m_transactionManager.active().forbidRegister(putTo);
        }
    }

    m_registerManager.useRegister(Register::LR());
    output().add(translator().BL(0, node->name()));

    // Unlocking registers for reuse
    for (int argId = 1; argId < node->arguments().size(); argId++) {
        Register& paramReg = Register::RegisterList()[argId];
        m_transactionManager.active().allowRegister(paramReg);
    }

    // Marking caller-saved registers as "tmp"
    for (int argId = 0; argId < 4; argId++) {
        Register& paramReg = Register::RegisterList()[argId];
        m_registerManager.replace(paramReg, RegisterData::Tmp());
    }

    if (wasR0busy) {
        Register& reg = m_registerManager.chooseRegister();

        // For us a function result is a tmp value, which we can't reuse later.
        if (m_registerManager.replace(reg, RegisterData::Tmp()) == 0) {
            output().add(translator().MOV_reg(reg, Register::R0()));
        }

        m_transactionManager.end();
        m_transactionManager.active().setResultRegister(reg);
    } else {
        m_transactionManager.end();
        m_transactionManager.active().setResultRegister(Register::R0());
    }
}

void CodeGeneratorAarch32::visitNode(AST::ProgramNode* program)
{
    for (auto* node : program->nodes()) {
        visitNode(node);
    }
}

void CodeGeneratorAarch32::visitNode(AST::IdentifierNode* node)
{
    int varId = m_varManager.getId(node->value());
    auto data = RegisterData(DataVariable, varId);
    auto& resRegister = m_registerManager.chooseRegister(data);

    if (m_registerManager.replace(resRegister, data) == 0) {
        output().add(translator().LDR_imm_offset(resRegister, Register::FP(), -m_varManager.getOffset(varId)));
    }
    m_transactionManager.active().setResultRegister(resRegister);
}

void CodeGeneratorAarch32::visitNode(AST::IntConstNode* node)
{
    auto data = RegisterData(DataConst, node->value());
    auto& resRegister = m_registerManager.chooseRegister(data);

    if (m_registerManager.replace(resRegister, data) == 0) {
        output().add(translator().MOVV_imm32(resRegister, node->value()));
    }
    m_transactionManager.active().setResultRegister(resRegister);
}

// Help generators

template <typename Callback>
void CodeGeneratorAarch32::genBinaryMathOperation(AST::BinaryOperationNode* node, Callback genAsm)
{
    m_transactionManager.create();
    visitNode(node->leftChild());
    Register& leftReg = m_transactionManager.active().resultRegister();
    m_transactionManager.active().forbidRegister(leftReg);
    visitNode(node->rightChild());
    Register& rightReg = m_transactionManager.active().resultRegister();
    m_transactionManager.end();

    // Saving result right operand
    Register& resultReg = m_registerManager.chooseRegister();
    if (m_registerManager.replace(resultReg, RegisterData::Tmp()) == 0) {
        genAsm(resultReg, leftReg, rightReg);
    }
    m_transactionManager.active().setResultRegister(resultReg);
}

template <typename Callback>
void CodeGeneratorAarch32::genBinaryCmpOperation(AST::BinaryOperationNode* node, Callback genAsm)
{
    m_transactionManager.create();
    visitNode(node->leftChild());
    Register& leftReg = m_transactionManager.active().resultRegister();
    m_transactionManager.active().forbidRegister(leftReg);
    visitNode(node->rightChild());
    Register& rightReg = m_transactionManager.active().resultRegister();
    m_transactionManager.end();

    genAsm(leftReg, rightReg);
}

void CodeGeneratorAarch32::genBinaryAssign(AST::BinaryOperationNode* node)
{
    m_transactionManager.create();
    visitNode(node->rightChild());
    Register& rightReg = m_transactionManager.active().resultRegister();
    m_transactionManager.end();

    auto identifierNode = reinterpret_cast<AST::IdentifierNode*>(node->leftChild());
    auto leftData = RegisterData(DataVariable, m_varManager.getId(identifierNode->value()));
    Register& leftReg = m_registerManager.chooseRegister(leftData);
    if (m_registerManager.replace(leftReg, leftData) == 0) {
        leftReg.data().set(leftData);
    }

    if (m_registerManager.write(leftReg) == 0) {
        if (leftReg != rightReg) {
            output().add(translator().MOV_reg(leftReg, rightReg));
        }
    }
}

void CodeGeneratorAarch32::initStackFrame(AST::FunctionNode* func)
{
    // TODO: Use func->statement()->statementsWithType(AST::NodeType::);
    m_varManager.enterScope();
    m_registerManager.useRegister(Register::FP());
    RegisterList used_reg_in_func = { Register::FP() };
    m_storage[STACK_SAVED_CALLEE_REGS_OP_ID] = output().add(translator().PUSH_multiple_registers(used_reg_in_func));
    output().add(translator().ADD_imm12(Register::FP(), Register::SP(), 4 * (used_reg_in_func.size() - 1)));
    allocateArgVars(func);
    allocateLocalVars(func);
}

void CodeGeneratorAarch32::restoreStackFrame(AST::FunctionNode* func)
{
    int pushOperationId = m_storage[STACK_SAVED_CALLEE_REGS_OP_ID];
    output().node(pushOperationId).setOpcode(translator().PUSH_multiple_registers(m_registerManager.usedRegisters()));

    output().add(translator().SUB_imm12(Register::SP(), Register::FP(), 4));
    output().add(translator().POP_multiple_registers(m_registerManager.usedRegisters()));
    output().add(translator().BX(Register::LR()));
    m_varManager.leaveScope();
}

int CodeGeneratorAarch32::allocateArgVars(AST::FunctionNode* func)
{
    int argVarsCount = func->arguments().size();
    int offset = 0;
    for (auto node : func->arguments()) {
        auto identifierNode = reinterpret_cast<AST::FunctionArgumentNode*>(node)->identifier();
        offset += 4; // 4 bytes
        int varId = m_varManager.addVariable(identifierNode->value());
        m_varManager.setOffset(varId, offset);
    }

    m_storage[FUNC_ARG_VARS] = argVarsCount;
    return 0;
}

int CodeGeneratorAarch32::allocateLocalVars(AST::FunctionNode* func)
{
    // FIXME: For now we use TernaryOperationNode when we allocate something on stack
    // like (int a;). We don't support multiple allocations in a row (int a, b;).
    // It will be fixed when we reimplement such allocation operations. For now we count
    // one TernaryOperation - one var allocated.
    int localVarsCount = 0;
    int offset = m_storage[FUNC_ARG_VARS] * 4; // Considering offset taken for vars from args.
    auto assignNodes = func->statement()->statementsWithType<AST::TernaryOperationNode>();
    for (auto node : assignNodes) {
        if (node->operation() == Lexer::TokenType::Assign) {
            auto identifierNode = reinterpret_cast<AST::IdentifierNode*>(node->middleChild());
            localVarsCount++;
            offset += 4; // 4 bytes
            int varId = m_varManager.addVariable(identifierNode->value());
            m_varManager.setOffset(varId, offset);
        }
    }

    // m_varManager.dump();

    m_storage[FUNC_LOCAL_VARS] = localVarsCount;
    output().add(translator().SUB_imm12(Register::SP(), Register::SP(), offset));
    return 0;
}

// Currently BooleanSnakeNode and BooleanOperation return different output.
// BooleanOperation doesn't have false branch and we need to handle that.
// We basicaly add a new false branch to the active transaction.
void CodeGeneratorAarch32::addFalseBranch(AST::Node* node)
{
    assert(m_transactionManager.active().trueBranchInstrId() != -1);
    if (m_transactionManager.active().falseBranchInstrId() == -1) {
        int rnd = rand() % 90 + 10;
        std::string falseLabel("AFB" + std::to_string(rnd));
        output().node(m_storage[OP_SAVED_PLACE_FALSE_BRANCH]).setOpcode(translator().BL(0, falseLabel));
        output().node(m_storage[OP_SAVED_PLACE_FALSE_BRANCH]).setVisible(true);
        m_transactionManager.active().setFalseBranchInstrId(output().addLabel(falseLabel));
    }
}

}