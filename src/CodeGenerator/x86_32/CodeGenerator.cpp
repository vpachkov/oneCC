#include "CodeGenerator.h"
#include "../../Lexer/Token.h"
#include "Common/ModRM.h"
#include "Common/Regs.h"

#include <utility>

namespace oneCC::CodeGenerator::X86_32 {

CodeGeneratorX86_32::CodeGeneratorX86_32()
{
    m_registerManager = RegisterManager({
        Register::EAX,
        Register::EBX,
        Register::ECX,
        Register::EDX,
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
    m_functionLabels[a->identifier()] = a->identifier()->value();

    //TODO: move it somewhere
    std::cout << m_functionLabels[a->identifier()] << ":" << std::endl;

    m_asmTranslator.PUSH_reg32(Register::EBP);
    m_asmTranslator.MOV_reg32_rm32(Register::EBP, RM(RMType::Reg, static_cast<uint32_t>(Register::ESP)));

    visitNode(a->statement());

    m_asmTranslator.POP_reg32(Register::EBP);
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
            m_asmTranslator.SUB_rm32_imm32(RM(RMType::Reg, static_cast<uint32_t>(Register::ESP)), variableOffset);

            visitNode(a->rightChild());

            // save result to allocated space
            auto resultRegister = static_cast<Register>(reinterpret_cast<AST::Expression*>(a->rightChild())->resultRegister());
            m_asmTranslator.MOV_rm32_reg32(RM(RMType::Mem, static_cast<uint32_t>(variableOffset + m_basePointerOffset)), resultRegister);
            m_registerManager.freeRegister(resultRegister);

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

void CodeGeneratorX86_32::visitNode(AST::ReturnStatementNode* a) {}
void CodeGeneratorX86_32::visitNode(AST::IfStatementNode* a) {}
void CodeGeneratorX86_32::visitNode(AST::WhileStatementNode* a) {}
void CodeGeneratorX86_32::visitNode(AST::FunctionCallNode* a) {}

void CodeGeneratorX86_32::visitNode(AST::IdentifierNode* a)
{
    int resultRegister = m_registerManager.allocateRegister();
    m_asmTranslator.MOV_reg32_rm32(static_cast<Register>(resultRegister), RM(RMType::Mem, static_cast<uint32_t>(m_scoper.getMemoryPosition(a))));
    a->setResultRegister(resultRegister);
}

void CodeGeneratorX86_32::visitNode(AST::IntConstNode* a)
{
    int reg = m_registerManager.allocateRegister();
    if (!reg) {
        // TODO: error here
        return;
    }
    a->setResultRegister(reg);
    m_asmTranslator.MOV_rm32_imm32(RM(RMType::Reg, (uint32_t)reg), a->value());
}

void CodeGeneratorX86_32::visitNode(AST::BinaryOperationNode* a)
{
    visitNode(a->leftChild());
    visitNode(a->rightChild());

    switch (a->operation()) {

    case Lexer::TokenType::Plus: {
        int leftRegister = reinterpret_cast<AST::Expression*>(a->leftChild())->resultRegister();
        int rightRegister = reinterpret_cast<AST::Expression*>(a->rightChild())->resultRegister();
        m_asmTranslator.ADD_rm32_reg32(
            RM(RMType::Reg, static_cast<uint32_t>(leftRegister)),
            static_cast<Register>(rightRegister));
        a->setResultRegister(leftRegister);
        m_registerManager.freeRegister(rightRegister);
        break;
    }
    case Lexer::TokenType::Assign : {
        visitNode(a->rightChild());
        auto exprRegister = static_cast<Register>(reinterpret_cast<AST::Expression*>(a->rightChild())->resultRegister());
        auto var = reinterpret_cast<AST::IdentifierNode*>(a->leftChild());
        m_asmTranslator.MOV_rm32_reg32(RM(RMType::Mem, static_cast<uint32_t>(m_scoper.getMemoryPosition(var))), exprRegister);
        m_registerManager.freeRegister(exprRegister);
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

}