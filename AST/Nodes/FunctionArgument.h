#pragma once
#include "../ASTNode.h"

namespace oneCC::AST {

class FunctionArgumentNode : public Node {
public:
    FunctionArgumentNode(Lexer::TokenType type, const std::string& name, Node* expression)
        : Node(servedType())
        , m_type(type)
        , m_name(name)
        , m_expression(expression)
    {
    }

    FunctionArgumentNode(Lexer::TokenType type, std::string&& name, Node* expression)
        : Node(servedType())
        , m_type(type)
        , m_name(std::move(name))
        , m_expression(expression)
    {
    }
    
    ~FunctionArgumentNode() override = default;

    Lexer::TokenType type() const { return m_type; }
    const std::string& name() const { return m_name; }
    Node* expression() const { return m_expression; }

    static NodeType servedType() { return FunctionArgument; }

private:
    Lexer::TokenType m_type;
    std::string m_name;
    Node* m_expression;
};

}