#include "CodeGenerator.h"
#include "Common/Regs.h"
#include "Common/ModRM.h"
#include "../../Lexer/Token.h"

#include <utility>

namespace oneCC::CodeGenerator::X86_32 {

CodeGeneratorX86_32::CodeGeneratorX86_32() {
    m_registerManager = RegisterManager({ Register::EAX, Register::EBX, Register::ECX, Register::EDX, });
}

int CodeGeneratorX86_32::processTree(AST::Node* program)
{
    return -1;
}

void CodeGeneratorX86_32::visitNode(AST::IdentifierNode* a)
{
    a->setResultRegister(m_registerManager.allocateRegister());
    // TODO: implement var allocator
}

    void CodeGeneratorX86_32::visitNode(AST::IntConstNode* a) {
        int reg = m_registerManager.allocateRegister();
        if (!reg){
            // TODO: error here
            return;
        }
        a->setResultRegister(reg);
        m_asmTranslator.MOV_rm32_imm32(RM(RMType::Reg, (uint32_t)reg), a->value());
    }

    void CodeGeneratorX86_32::visitNode(AST::BinaryOperationNode* a) {
        visitNode(a->leftChild());
        visitNode(a->rightChild());

        switch (a->operation()) {
            case Lexer::TokenType::Plus: {
                int leftRegister = reinterpret_cast<AST::Expression*>(a->leftChild())->resultRegister();
                int rightRegister = reinterpret_cast<AST::Expression*>(a->rightChild())->resultRegister();
                m_asmTranslator.ADD_rm32_reg32(
                    RM(RMType::Reg, static_cast<uint32_t>(leftRegister)),
                    static_cast<Register>(rightRegister)
                );
                a->setResultRegister(leftRegister);
                m_registerManager.freeRegister(rightRegister);
            }
        }
    }

int CodeGeneratorX86_32::generateLabel() {
    return m_labelCount++;
}

}