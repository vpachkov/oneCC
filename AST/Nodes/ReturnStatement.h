#pragma once
#include "../ASTNode.h"
#include <string>
#include <utility>

namespace oneCC::AST {

class ReturnStatementNode : public Node {
public:
    ReturnStatementNode() : Node(WhileStatement) { };
    explicit ReturnStatementNode(Node* expression, Node* statement)
            : Node(Identifier)
            , m_expression(expression)
            , m_statement(statement) {}

    ~ReturnStatementNode() override = default;

    Node* expression() const { return m_expression; }
    Node* statement() const { return m_statement; }

private:
    Node* m_expression{};
    Node* m_statement{};
};

}