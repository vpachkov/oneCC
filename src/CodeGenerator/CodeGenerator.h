#pragma once

#include "../AST/AbstractAST.h"
#include "../Lexer/Token.h"
#include <cstdint>
#include <iostream>
#include <string>
#include <map>
#include <stack>

namespace oneCC::CodeGenerator {

class CodeGenerator final : public AST::AbstractAST {
public:
    CodeGenerator() = default;
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
    void visitNode(AST::WhileStatementNode* a) override;
    void visitNode(AST::FunctionNode* a) override;
    void visitNode(AST::FunctionCallNode* a) override;
    void visitNode(AST::ProgramNode* a) override;
};

}