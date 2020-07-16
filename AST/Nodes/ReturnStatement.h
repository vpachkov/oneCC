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
    
    explicit ReturnStatementNode(Node* returnedExpression, Node* function)
        : Node(servedType())
        , m_returnedExpression(returnedExpression)
        , m_function(function)
    {
    }

    ~ReturnStatementNode() override = default;

    Node* returnedExpression() const { return m_returnedExpression; }
    Node* function() const { return m_function; }

    static NodeType servedType() { return ReturnStatement; }

private:
    Node* m_returnedExpression;
    Node* m_function;
};

}