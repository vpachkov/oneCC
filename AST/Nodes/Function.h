#pragma once
#include "../ASTNode.h"
#include <utility>
#include <vector>

namespace oneCC::AST {

class FunctionNode : public Node {
public:
    FunctionNode() : Node(Function) { }
    FunctionNode(Node* type, Node* name, std::vector<Node*>  arguments, Node* statement)
            : Node(Function)
            , m_type(type)
            , m_name(name)
            , m_arguments(std::move(arguments))
            , m_statement(statement){ }

    ~FunctionNode() override = default;

    void setType(Node* type) { m_type = type; }
    void setName(Node* name) { m_name = name; }
    void setArguments(std::vector<Node*> arguments) { m_arguments = std::move(arguments); }

    Node* type() { return m_type; }
    Node* name() { return m_name; }
    std::vector<Node*> arguments() { return m_arguments; }

private:
    Node* m_type {};
    Node* m_name {};
    std::vector<Node*> m_arguments {};
    Node* m_statement {};

};

}
