#include "CodeGenerator.h"
#include "../../Lexer/Token.h"
#include "Common/ModRM.h"
#include "Common/Regs.h"

#include <sstream>
#include <utility>

namespace oneCC::CodeGenerator::X86_32 {

CodeGeneratorX86_32::CodeGeneratorX86_32()
{
    m_registerManager = RegisterManager({
        Register::EBX,
        Register::ECX,
        Register::EDX,
        Register::EAX,
    });
}

int CodeGeneratorX86_32::processTree(AST::Node* program)
{
    visitNode(program);
    return 0;
}
void CodeGeneratorX86_32::visitNode(AST::ProgramNode* a) {
    for (auto* node : a->nodes()) {
        visitNode(node);
    }
}

void CodeGeneratorX86_32::visitNode(AST::FunctionNode* a) {
    // Generating function header TODO: move it somewhere
    m_functionLabels[a->identifier()->value()] = generateFunctionLabel(a);
    std::cout << std::endl << m_functionLabels[a->identifier()->value()] << ":" << std::endl;

    m_asmTranslator.PUSH_reg32(Register::EBP);
    m_asmTranslator.MOV_reg32_rm32(Register::EBP, RM(RMType::Reg, Register::ESP));
    m_basePointerOffset = 0;

    Register reversedFastcallRegisters[] = { Register::ECX, Register::EDX, Register::EAX };
    size_t fastcallRegistersIndex = 3 - a->arguments().size();

    // save arguments to the scoper
    int variableOffset = 0;
    for (auto arg = a->arguments().rbegin(); arg < a->arguments().rend(); arg++) {
        auto argId = reinterpret_cast<AST::FunctionArgumentNode *>(*arg)->identifier();
        m_scoper.addNode(argId, 1); // offset is equal to 1, because of we are not in the function body yet

        if (a->arguments().size() > 3) { // means variables are already in the memory
            variableOffset -= 4;
            m_scoper.setMemoryPosition(argId, variableOffset);
        } else { // variables are stored in registers
            int typeOffset = 4; // int TODO: calculate it, based on type
            m_asmTranslator.MOV_rm32_reg32(RM(RMType::Mem, typeOffset + m_basePointerOffset), reversedFastcallRegisters[fastcallRegistersIndex]);
            m_basePointerOffset += typeOffset;
            m_scoper.setMemoryPosition(argId, m_basePointerOffset);
        }

        fastcallRegistersIndex++;
    }

    visitNode(a->statement());

    m_asmTranslator.MOV_reg32_rm32(Register::ESP, RM(RMType::Reg, Register::EBP));
    m_asmTranslator.POP_reg32(Register::EBP);
    m_asmTranslator.RETF();
}

void CodeGeneratorX86_32::visitNode(AST::BlockStatementNode* a) {
    m_scoper.enterScope();
    for (auto* statement : a->statements()) {
        visitNode(statement);
    }
    m_scoper.exitScope();
}

void CodeGeneratorX86_32::visitNode(AST::TernaryOperationNode* a) {
    switch (a->operation()) {
        case Lexer::TokenType::Assign: {
            // TODO: offset should be calculated by the type (now it's 4)
            int variableOffset = 4; // double word (integer)
            // allocate space for variable
            m_asmTranslator.SUB_rm32_imm32(RM(RMType::Reg, Register::ESP), variableOffset);

            if (a->rightChild()->type() != AST::NodeType::Const) {
                visitNode(a->rightChild());
                // save result to allocated space
                auto resultRegister = static_cast<Register>(reinterpret_cast<AST::Expression *>(a->rightChild())->resultRegister());
                m_asmTranslator.MOV_rm32_reg32(RM(RMType::Mem, variableOffset + m_basePointerOffset), resultRegister);
                m_registerManager.freeRegister(resultRegister);
            } else { // we can save const variables immediately
                auto value = reinterpret_cast<AST::IntConstNode*>(a->rightChild())->value();
                m_asmTranslator.MOV_rm32_imm32(RM(RMType::Mem, variableOffset + m_basePointerOffset), value);
            }

            // move base offset pointer for next variable
            m_basePointerOffset += variableOffset;

            // save variable position in memory
            auto* var = reinterpret_cast<AST::IdentifierNode*>(a->middleChild());
            m_scoper.addNode(var);
            m_scoper.setMemoryPosition(var, m_basePointerOffset);

        }
        default:
            return;
    }
}

void CodeGeneratorX86_32::visitNode(AST::ReturnStatementNode* a) {
    visitNode(a->returnedExpression());
    auto resultRegister = static_cast<Register>(reinterpret_cast<AST::Expression*>(a->returnedExpression())->resultRegister());
    if (resultRegister != Register::EAX) {
        m_asmTranslator.MOV_reg32_rm32(Register::EAX, RM(RMType::Reg, resultRegister));
        m_registerManager.freeRegister(resultRegister);
    }
}

void CodeGeneratorX86_32::visitNode(AST::IfStatementNode* a) {}
void CodeGeneratorX86_32::visitNode(AST::WhileStatementNode* a) {}

void CodeGeneratorX86_32::visitNode(AST::FunctionCallNode* a) {
    Register fastcallRegisters[] = { Register::EAX, Register::EDX, Register::ECX };
    size_t fastcallRegistersIndex = 0;

    for (auto* arg : a->arguments()) {
        visitNode(arg);
        auto resultReg = static_cast<Register>(reinterpret_cast<AST::Expression*>(arg)->resultRegister());
        if (a->arguments().size() > 3) { // according to FASTCALL convention
            m_asmTranslator.PUSH_reg32(resultReg);
            m_registerManager.freeRegister(resultReg);
        }
        else if (resultReg != fastcallRegisters[fastcallRegistersIndex]) {
            m_asmTranslator.MOV_reg32_rm32(fastcallRegisters[fastcallRegistersIndex], RM(RMType::Reg, resultReg));
            m_registerManager.freeRegister(resultReg);
        }

        fastcallRegistersIndex++;
    }

    m_asmTranslator.CALL_label(m_functionLabels[a->name()]);
    a->setResultRegister(Register::EAX);
}

void CodeGeneratorX86_32::visitNode(AST::IdentifierNode* a)
{
    int resultRegister = m_registerManager.allocateRegister();
    m_asmTranslator.MOV_reg32_rm32(static_cast<Register>(resultRegister), RM(RMType::Mem, m_scoper.getMemoryPosition(a)));
    a->setResultRegister(resultRegister);
}

void CodeGeneratorX86_32::visitNode(AST::IntConstNode* a)
{
    int reg = m_registerManager.allocateRegister();
    a->setResultRegister(reg);
    m_asmTranslator.MOV_rm32_imm32(RM(RMType::Reg, reg), static_cast<uint32_t>(a->value()));

}

void CodeGeneratorX86_32::visitNode(AST::BinaryOperationNode* a)
{
    switch (a->operation()) {

    case Lexer::TokenType::Plus: {

        visitNode(a->leftChild());
        int leftRegister = reinterpret_cast<AST::Expression*>(a->leftChild())->resultRegister();

        if (a->rightChild()->type() != AST::NodeType::Const) {
            visitNode(a->rightChild());
            int rightRegister = reinterpret_cast<AST::Expression *>(a->rightChild())->resultRegister();
            m_asmTranslator.ADD_rm32_reg32(
                    RM(RMType::Reg, static_cast<uint32_t>(leftRegister)),
                    static_cast<Register>(rightRegister));
            a->setResultRegister(leftRegister);
            m_registerManager.freeRegister(rightRegister);
        } else {
            auto value = reinterpret_cast<AST::IntConstNode*>(a->rightChild())->value();
            m_asmTranslator.ADD_rm32_imm32(RM(RMType::Reg, static_cast<uint32_t>(leftRegister)), value);
        }
        break;
    }
    case Lexer::TokenType::Assign : {
        auto var = reinterpret_cast<AST::IdentifierNode*>(a->leftChild());

        if (a->rightChild()->type() != AST::NodeType::Const) {
            visitNode(a->rightChild());
            auto exprRegister = static_cast<Register>(reinterpret_cast<AST::Expression *>(a->rightChild())->resultRegister());
            m_asmTranslator.MOV_rm32_reg32(RM(RMType::Mem, m_scoper.getMemoryPosition(var)), exprRegister);
            m_registerManager.freeRegister(exprRegister);
        } else {
            auto value = reinterpret_cast<AST::IntConstNode*>(a->rightChild())->value();
            m_asmTranslator.MOV_rm32_imm32(RM(RMType::Mem, m_scoper.getMemoryPosition(var)), value);
        }
        break;
    }

    default: {
        return;
    }

    }
}

int CodeGeneratorX86_32::generateLabel()
{
    return m_labelCount++;
}
// examples: main(), square(int)
std::string CodeGeneratorX86_32::generateFunctionLabel(AST::FunctionNode* function) {

    std::stringstream functionLabel;
    functionLabel << function->identifier()->value() << "(";

    for (int i = 0 ; i < function->arguments().size() ; i++) {
        functionLabel << Lexer::tokenTypeToString(reinterpret_cast<AST::FunctionArgumentNode*>(function->arguments()[i])->identifier()->expressionType());
        if (i < function->arguments().size() - 1) {
            functionLabel << ", ";
        }
    }

    functionLabel << ")";

    return functionLabel.str();
}

}