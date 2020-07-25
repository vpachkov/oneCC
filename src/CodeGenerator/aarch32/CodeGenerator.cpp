#include "CodeGenerator.h"
#include <iostream>

namespace oneCC::CodeGenerator::Aarch32 {

int CodeGeneratorAarch32::processTree(AST::Node* program)
{
    visitNode(program);
    return 0;
}

void CodeGeneratorAarch32::visitNode(AST::BinaryOperationNode* a) {}
void CodeGeneratorAarch32::visitNode(AST::TernaryOperationNode* a) {}
void CodeGeneratorAarch32::visitNode(AST::IdentifierNode* a) {}
void CodeGeneratorAarch32::visitNode(AST::BlockStatementNode* a) {}
void CodeGeneratorAarch32::visitNode(AST::ReturnStatementNode* a) {}
void CodeGeneratorAarch32::visitNode(AST::IfStatementNode* a) {}
void CodeGeneratorAarch32::visitNode(AST::WhileStatementNode* a) {}

void CodeGeneratorAarch32::visitNode(AST::FunctionNode* func)
{
    m_translator.addLabel(func->identifier()->value().c_str());
    initStackFrame(func);
    m_translator.addLabel("...");
    restoreStackFrame(func);
    m_translator.addLabel("");
}

void CodeGeneratorAarch32::visitNode(AST::FunctionCallNode* a) {}

void CodeGeneratorAarch32::visitNode(AST::ProgramNode* program) 
{
    for (auto* node : program->nodes()) {
        visitNode(node);
    }
}

void CodeGeneratorAarch32::initStackFrame(AST::FunctionNode* func)
{
    // TODO: Use func->statement()->statementsWithType(AST::NodeType::);
    int countOfVars = 2;
    m_storage[FUNC_LOCAL_VARS] = countOfVars;
    RegisterList used_reg_in_func = { Register::fp };
    m_translator.PUSH_multiple_registers(used_reg_in_func);
    m_translator.ADD_imm12(Register::fp, Register::sp, 4);
    m_translator.SUB_imm12(Register::sp, Register::sp, 4 * countOfVars);
}

void CodeGeneratorAarch32::restoreStackFrame(AST::FunctionNode* func)
{
    m_translator.SUB_imm12(Register::sp, Register::fp, 4);
    m_translator.POP_multiple_registers({ Register::fp });
    m_translator.BX(Register::lr);
}

}