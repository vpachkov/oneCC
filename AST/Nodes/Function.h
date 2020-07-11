#pragma once
#include "../ASTNode.h"
#include <utility>
#include <vector>

namespace oneCC::AST {

class FunctionNode : public Node {
public:
    FunctionNode()
        : Node(Function)
    {
    }

    FunctionNode(Node* type, Node* name, const std::vector<Node*>& arguments, Node* statement)
        : Node(Function)
        , m_type(type)
        , m_name(name)
        , m_arguments(arguments)
        , m_statement(statement)
    {
    }

    FunctionNode(Node* type, Node* name, std::vector<Node*>&& arguments, Node* statement)
        : Node(Function)
        , m_type(type)
        , m_name(name)
        , m_arguments(std::move(arguments))
        , m_statement(statement)
    {
    }

    ~FunctionNode() override = default;

    void setType(Node* type) { m_type = type; }
    void setName(Node* name) { m_name = name; }
    void setArguments(std::vector<Node*> arguments) { m_arguments = arguments; }
    void setArguments(std::vector<Node*>&& arguments) { m_arguments = arguments; }

    Node* type() const { return m_type; }
    Node* name() const { return m_name; }
    const std::vector<Node*>& arguments() const { return m_arguments; }

private:
    Node* m_type {};
    Node* m_name {};
    std::vector<Node*> m_arguments {};
    Node* m_statement {};
};

}
