#pragma once
#include "../ASTNode.h"
#include <utility>
#include <vector>
#include <string>

namespace oneCC::AST {

class FunctionNode : public Node {
public:
    FunctionNode()
        : Node(Function)
    {
    }

    FunctionNode(Lexer::TokenType type, const std::string& name, const std::vector<Node*>& arguments, Node* statement)
        : Node(Function)
        , m_type(type)
        , m_name(name)
        , m_arguments(arguments)
        , m_statement(statement)
    {
    }

    FunctionNode(Lexer::TokenType type, const std::string& name, std::vector<Node*>&& arguments, Node* statement)
        : Node(Function)
        , m_type(type)
        , m_name(name)
        , m_arguments(std::move(arguments))
        , m_statement(statement)
    {
    }

    ~FunctionNode() override = default;

    void setType(Lexer::TokenType type) { m_type = type; }
    void setName(const std::string& name) { m_name = name; }
    void setArguments(std::vector<Node*> arguments) { m_arguments = arguments; }
    void setArguments(std::vector<Node*>&& arguments) { m_arguments = arguments; }

    Lexer::TokenType type() const { return m_type; }
    const std::string& name() const { return m_name; }
    Node* statement() const { return m_statement; }
    const std::vector<Node*>& arguments() const { return m_arguments; }

private:
    Lexer::TokenType m_type {};
    std::string m_name {};
    std::vector<Node*> m_arguments {};
    Node* m_statement {};
};

}
