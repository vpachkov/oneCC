#pragma once
#include "../ASTNode.h"
#include <string>
#include <utility>

namespace oneCC::AST {

class ReturnStatementNode : public Node {
public:
    ReturnStatementNode()
        : Node(servedType())
    {
    }
    
    explicit ReturnStatementNode(Node* returnedExpression)
        : Node(servedType())
        , m_returnedExpression(returnedExpression)
    {
    }

    ~ReturnStatementNode() override = default;

    Node* returnedExpression() const { return m_returnedExpression; }

    static NodeType servedType() { return ReturnStatement; }

private:
    Node* m_returnedExpression;
};

}