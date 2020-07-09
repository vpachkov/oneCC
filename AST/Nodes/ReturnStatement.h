#pragma once
#include "../ASTNode.h"
#include <string>
#include <utility>

namespace oneCC::AST {

class ReturnStatementNode : public Node {
public:
    ReturnStatementNode() : Node(ReturnStatement) { }
    explicit ReturnStatementNode(Node* returnedExpression)
            : Node(ReturnStatement)
            , m_returnedExpression(returnedExpression) { }

    ~ReturnStatementNode() override = default;

    Node* returnedExpression() const { return m_returnedExpression; }

private:
    Node* m_returnedExpression {};
};

}