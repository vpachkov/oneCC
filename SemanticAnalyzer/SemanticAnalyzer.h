#pragma once
#include "../AST/AbstractAST.h"
#include "../Lexer/Token.h"
#include "Scoper/Scoper.h"
#include <cstdint>
#include <iostream>
#include <string>
#include <map>
#include <stack>

namespace oneCC::SemanticAnalyzer {

class SemanticAnalyzer final : public AST::AbstractAST {
public:
    SemanticAnalyzer() = default;
    bool processTree(AST::Node* program);

private:

    // From AST::AbstractAST
    using AST::AbstractAST::visitNode;
    void visitNode(AST::BinaryOperationNode* a) override;
    void visitNode(AST::TernaryOperationNode* a) override;
    void visitNode(AST::IdentifierNode* a) override;
    void visitNode(AST::BlockStatementNode* a) override;
    void visitNode(AST::ReturnStatementNode* a) override;
    void visitNode(AST::IfStatementNode* a) override;
    void visitNode(AST::FunctionNode* a) override;
    void visitNode(AST::FunctionCallNode* a) override;
    void visitNode(AST::ProgramNode* a) override;

    bool isConvertationCorrect(Lexer::TokenType a, Lexer::TokenType b) {
        return true;
    }

    std::map<std::string, AST::FunctionNode*> m_functions {};
    Scoper m_scoper {};
    bool m_errorFlag { false };
};
}