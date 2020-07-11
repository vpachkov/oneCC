#pragma once
#include "../ASTNode.h"

namespace oneCC::AST {

class FunctionArgumentNode : public Node {
public:
    FunctionArgumentNode(Lexer::TokenType type, const std::string& name)
        : Node(FunctionArgument)
        , m_type(type)
        , m_name(name)
    {
    }

    FunctionArgumentNode(Lexer::TokenType type, std::string&& name)
        : Node(FunctionArgument)
        , m_type(type)
        , m_name(std::move(name))
    {
    }
    
    ~FunctionArgumentNode() override = default;

    Lexer::TokenType type() const { return m_type; }
    const std::string& name() const { return m_name; }

private:
    Lexer::TokenType m_type;
    std::string m_name;
};

}