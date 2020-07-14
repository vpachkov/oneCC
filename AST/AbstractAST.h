#pragma once

#include "ASTNode.h"
#include "Nodes/BinaryOperation.h"
#include "Nodes/BlockStatement.h"
#include "Nodes/Function.h"
#include "Nodes/FunctionArgument.h"
#include "Nodes/FunctionCall.h"
#include "Nodes/Identifier.h"
#include "Nodes/IntConst.h"
#include "Nodes/Program.h"
#include "Nodes/ReturnStatement.h"
#include "Nodes/TernaryOperation.h"
#include "Nodes/Type.h"
#include <iostream>
#include <string>
#include <vector>

#ifndef convertASTNode
// It tries to convert the node into diverted type, if it's possible and leave the function.
#define convertASTNode(x)                       \
    if (node->type() == x::servedType()) {      \
        auto* ptr = reinterpret_cast<x*>(node); \
        visitNode(ptr);                         \
        return;                                 \
    }
#endif // convertASTNode

namespace oneCC::AST {

class AbstractAST {
public:
    AbstractAST() = default;

    AbstractAST(Node* root)
        : m_root(root)
    {
    }

    virtual ~AbstractAST() = default;

    void visitNode(Node* node)
    {
        convertASTNode(AST::IntConstNode);

        convertASTNode(AST::BinaryOperationNode);
        convertASTNode(AST::TernaryOperationNode);

        convertASTNode(AST::TypeNode);
        convertASTNode(AST::IdentifierNode);

        convertASTNode(AST::BlockStatementNode);
        convertASTNode(AST::ReturnStatementNode);

        convertASTNode(AST::FunctionNode);
        convertASTNode(AST::FunctionArgumentNode);
        convertASTNode(AST::FunctionCallNode);

        convertASTNode(AST::ProgramNode);
    }

    virtual void visitNode(BinaryOperationNode*) {}
    virtual void visitNode(TernaryOperationNode*) {} 
    virtual void visitNode(TypeNode*) {}
    virtual void visitNode(IdentifierNode*) {}

    virtual void visitNode(BlockStatementNode*) {}
    virtual void visitNode(ReturnStatementNode*) {}

    virtual void visitNode(FunctionNode*) {}
    virtual void visitNode(FunctionArgumentNode*) {}
    virtual void visitNode(FunctionCallNode*) {}

    virtual void visitNode(ProgramNode*) {}

    virtual void visitNode(IntConstNode*) {}

    void setRoot(Node* root)
    {
        if (!root)
            return;
        m_root = root;
    }

    Node* root() { return m_root; }

private:
    Node* m_root { nullptr };
};

}