#include "CodeGenerator.h"
#include <iostream>

namespace oneCC::CodeGenerator::Aarch32 {

int CodeGeneratorAarch32::processTree(AST::Node* program)
{
    visitNode(program);
    return 0;
}

void CodeGeneratorAarch32::visitNode(AST::BinaryOperationNode* a) {}

void CodeGeneratorAarch32::visitNode(AST::TernaryOperationNode* node) 
{
    if (m_storage[FUNC_PROCESSING] == 1) {
        if (node->rightChild()) {
            auto* identifierNode = reinterpret_cast<AST::IdentifierNode*>(node->middleChild());
            auto& assignTransaciton = m_registerManager.initiateTransaction();
            visitNode(node->rightChild());
            std::cout << "Store " << assignTransaciton.getResultRegister().textAlias() << " at [fp -" << m_varManager.getOffset(identifierNode->value()) << "]\n";
            m_registerManager.didTransaction(assignTransaciton);
        }
    } else {
        // We are no in func, seems a global
    }
}

void CodeGeneratorAarch32::visitNode(AST::IdentifierNode* a) {}
void CodeGeneratorAarch32::visitNode(AST::BlockStatementNode* blk) 
{
    for (auto* node : blk->statements()) {
        visitNode(node);
    }
}
void CodeGeneratorAarch32::visitNode(AST::ReturnStatementNode* a) {}
void CodeGeneratorAarch32::visitNode(AST::IfStatementNode* a) {}
void CodeGeneratorAarch32::visitNode(AST::WhileStatementNode* a) {}

void CodeGeneratorAarch32::visitNode(AST::FunctionNode* func)
{
    m_storage[FUNC_PROCESSING] = 1;
    m_translator.addLabel(func->identifier()->value().c_str());
    initStackFrame(func);
    m_translator.addLabel("...");

    visitNode(func->statement());

    m_translator.addLabel("...");
    restoreStackFrame(func);
    m_translator.addLabel("");
    m_storage[FUNC_PROCESSING] = 0;
}

void CodeGeneratorAarch32::visitNode(AST::FunctionCallNode* a) {}

void CodeGeneratorAarch32::visitNode(AST::ProgramNode* program) 
{
    for (auto* node : program->nodes()) {
        visitNode(node);
    }
}

void CodeGeneratorAarch32::visitNode(AST::IntConstNode* node) 
{
    auto& resRegister = m_registerManager.chooseRegister();
    m_translator.MOVV_imm32(resRegister, node->value());
    m_registerManager.activeTransaction().setResultRegister(resRegister);
}

void CodeGeneratorAarch32::initStackFrame(AST::FunctionNode* func)
{
    // TODO: Use func->statement()->statementsWithType(AST::NodeType::);
    m_varManager.enterScope();
    RegisterList used_reg_in_func = { Register::FP() };
    m_translator.PUSH_multiple_registers(used_reg_in_func);
    m_translator.ADD_imm12(Register::FP(), Register::SP(), 4 * (used_reg_in_func.size() - 1));
    allocateArgVars(func);
    allocateLocalVars(func);
}

void CodeGeneratorAarch32::restoreStackFrame(AST::FunctionNode* func)
{
    m_translator.SUB_imm12(Register::SP(), Register::FP(), 4);
    m_translator.POP_multiple_registers({ Register::FP() });
    m_translator.BX(Register::LR());
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

    m_varManager.dump();

    m_storage[FUNC_LOCAL_VARS] = localVarsCount;
    m_translator.SUB_imm12(Register::SP(), Register::SP(), offset);
    return 0;
}

}