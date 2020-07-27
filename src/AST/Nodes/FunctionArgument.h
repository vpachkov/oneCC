#pragma once
#include "../ASTNode.h"
#include "Identifier.h"

namespace oneCC::AST {

class FunctionArgumentNode : public Node {
public:
    FunctionArgumentNode(IdentifierNode* identifier, Node* expression)
        : Node(servedType())
        , m_identifier(identifier)
        , m_expression(expression)
    {
    }
    
    ~FunctionArgumentNode() override = default;

    IdentifierNode* identifier() const { return m_identifier; }
    Node* expression() const { return m_expression; }

    static NodeType servedType() { return FunctionArgument; }

private:
    IdentifierNode* m_identifier {};
    Node* m_expression {};
};

}