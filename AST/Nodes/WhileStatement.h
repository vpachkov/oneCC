#pragma once
#include "../ASTNode.h"
#include <string>
#include <utility>

namespace oneCC::AST {

class WhileStatementNode : public Node {
public:
    WhileStatementNode() : Node(WhileStatement) { };
    explicit WhileStatementNode(Node* expression, Node* statement)
            : Node(WhileStatement)
            , m_expression(expression)
            , m_statement(statement) { }

    ~WhileStatementNode() override = default;

    Node* expression() const { return m_expression; }
    Node* statement() const { return m_statement; }

private:
    Node* m_expression {};
    Node* m_statement {};
};

}