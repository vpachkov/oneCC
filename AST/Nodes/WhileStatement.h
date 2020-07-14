#pragma once
#include "../ASTNode.h"
#include <string>
#include <utility>

namespace oneCC::AST {

class WhileStatementNode : public Node {
public:
    WhileStatementNode()
        : Node(servedType()) {};
    
    explicit WhileStatementNode(Node* expression, Node* statement)
        : Node(servedType())
        , m_expression(expression)
        , m_statement(statement)
    {
    }

    ~WhileStatementNode() override = default;

    Node* expression() const { return m_expression; }
    Node* statement() const { return m_statement; }

    static NodeType servedType() { return WhileStatement; }

private:
    Node* m_expression {};
    Node* m_statement {};
};

}