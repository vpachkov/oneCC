#pragma once

#include "../../AST/AbstractAST.h"
#include "../../Lexer/Token.h"
#include "Common/Regs.h"
#include "Output/OutputManager.h"
#include "Managers/RegisterManager.h"
#include "Managers/TransactionManager.h"
#include "Managers/VarManager.h"
#include "Translators/AsmTranslator.h"
#include <cstdint>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>

namespace oneCC::CodeGenerator::Aarch32 {

enum StorageKeys {
    FUNC_MAIN_LABEL,
    STACK_SAVED_CALLEE_REGS_OP_ID,
    FUNC_PROCESSING,
    FUNC_ARG_VARS,
    FUNC_LOCAL_VARS,
    LAUNCH_TRANSACTION,
    OP_INVERSED,
};

class CodeGeneratorAarch32 final : public AST::AbstractAST {
public:
    CodeGeneratorAarch32();

    int processTree(AST::Node* program);

    AsmTranslator& translator() { return m_translator; }
    RegisterManager& registerManager() { return m_registerManager; }
    TransactionManager& transactionManager() { return m_transactionManager; }
    VarManager& varManager() { return m_varManager; }
    OutputManager& outputManager() { return m_outputManager; }
    OutputManager& output() { return m_outputManager; }

private:
    // From AST::AbstractAST
    using AST::AbstractAST::visitNode;
    void visitNode(AST::BinaryOperationNode* a) override;
    void visitNode(AST::TernaryOperationNode* a) override;
    void visitNode(AST::IdentifierNode* a) override;
    void visitNode(AST::BlockStatementNode* a) override;
    void visitNode(AST::ReturnStatementNode* a) override;
    void visitNode(AST::IfStatementNode* a) override;
    void visitNode(AST::WhileStatementNode* a) override;
    void visitNode(AST::BooleanSnakeNode* a) override;
    void visitNode(AST::FunctionNode* a) override;
    void visitNode(AST::FunctionCallNode* a) override;
    void visitNode(AST::ProgramNode* a) override;
    void visitNode(AST::IntConstNode* a) override;

    template <typename Callback>
    void genBinaryMathOperation(AST::BinaryOperationNode* node, Callback genAsm);
    void genBinaryAssign(AST::BinaryOperationNode* node);
    void initStackFrame(AST::FunctionNode* func);
    void restoreStackFrame(AST::FunctionNode* func);
    int allocateArgVars(AST::FunctionNode* func);
    int allocateLocalVars(AST::FunctionNode* func);

    AsmTranslator m_translator;
    OutputManager m_outputManager;
    RegisterManager m_registerManager;
    TransactionManager m_transactionManager;
    VarManager m_varManager;

    // Storage is used as a unique place to store some values and
    // delivery some values through functions.
    std::unordered_map<int, int> m_storage;
};

}