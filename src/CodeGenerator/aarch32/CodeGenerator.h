#pragma once

#include "../../AST/AbstractAST.h"
#include "../../Lexer/Token.h"
#include "Translators/AsmTranslator.h"
#include <cstdint>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>

namespace oneCC::CodeGenerator::Aarch32 {

enum StorageKeys {
    FUNC_LOCAL_VARS,
};

class CodeGeneratorAarch32 final : public AST::AbstractAST {
public:
    CodeGeneratorAarch32()
        : m_translator()
        , m_storage()
    {
    }

    int processTree(AST::Node* program);

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
    void visitNode(AST::FunctionNode* a) override;
    void visitNode(AST::FunctionCallNode* a) override;
    void visitNode(AST::ProgramNode* a) override;

    void initStackFrame(AST::FunctionNode* func);
    void restoreStackFrame(AST::FunctionNode* func);

    AsmTranslator m_translator;
    std::unordered_map<int, int> m_storage;
};

}