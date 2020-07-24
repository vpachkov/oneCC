#pragma once
#include "../ASTNode.h"
#include <string>
#include <utility>

namespace oneCC::AST {

class IfStatementNode : public Node {
public:
    IfStatementNode()
        : Node(servedType())
    {
    }
    
    explicit IfStatementNode(Node* expression, Node* trueStatement, Node* falseStatement)
        : Node(servedType())
        , m_expression(expression)
        , m_trueStatement(trueStatement)
        , m_falseStatement(falseStatement)
    {
    }

    ~IfStatementNode() override = default;

    Node* expression() const { return m_expression; }
    Node* trueStatement() const { return m_trueStatement; }
    Node* falseStatement() const { return m_falseStatement; }

    static NodeType servedType() { return IfStatement; }

private:
    Node* m_expression;
    Node* m_trueStatement;
    Node* m_falseStatement;
};

}