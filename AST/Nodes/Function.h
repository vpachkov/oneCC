#pragma once
#include "../ASTNode.h"
#include "Identifier.h"
#include <utility>
#include <vector>
#include <string>

namespace oneCC::AST {

class FunctionNode : public Node {
public:
    FunctionNode()
        : Node(servedType())
    {
    }

    FunctionNode(IdentifierNode* identifier, const std::vector<Node*>& arguments, Node* statement)
        : Node(servedType())
        , m_identifier(identifier)
        , m_arguments(arguments)
        , m_statement(statement)
    {
    }

    FunctionNode(IdentifierNode* identifier, std::vector<Node*>&& arguments, Node* statement)
        : Node(servedType())
        , m_identifier(identifier)
        , m_arguments(std::move(arguments))
        , m_statement(statement)
    {
    }

    ~FunctionNode() override = default;

    void setIdentifier(IdentifierNode* identifier) {m_identifier = identifier; }
    void setArguments(std::vector<Node*> arguments) { m_arguments = arguments; }
    void setArguments(std::vector<Node*>&& arguments) { m_arguments = arguments; }
    void setStatement(Node* statement) { m_statement = statement; }

    IdentifierNode* identifier() const { return m_identifier; }
    Node* statement() const { return m_statement; }
    const std::vector<Node*>& arguments() const { return m_arguments; }

    static NodeType servedType() { return Function; }

private:
    IdentifierNode* m_identifier {};
    std::vector<Node*> m_arguments {};
    Node* m_statement {};
};

}
