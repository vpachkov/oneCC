#pragma once
#include "../ASTNode.h"
#include "Expression.h"
#include <string>

namespace oneCC::AST {

class IdentifierNode : public Expression {
public:
    IdentifierNode()
        : Expression(servedType())
    {
    }

    explicit IdentifierNode(const std::string& value)
        : Expression(servedType())
        , m_value(value)
    {
    }

    explicit IdentifierNode(const std::string& value, Lexer::TokenType token)
        : Expression(servedType(), token)
        , m_value(value)
    {
    }

    explicit IdentifierNode(std::string&& value)
        : Expression(servedType())
        , m_value(std::move(value))
    {
    }

    ~IdentifierNode() override = default;

    const std::string& value() const { return m_value; }

    static NodeType servedType() { return Identifier; }

private:
    std::string m_value {};
};

}