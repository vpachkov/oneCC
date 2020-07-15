#pragma once
#include "../ASTNode.h"
#include <string>

namespace oneCC::AST {

class IdentifierNode : public Node {
public:
    IdentifierNode()
        : Node(servedType())
    {
    }

    explicit IdentifierNode(const std::string& value)
        : Node(servedType())
        , m_value(value)
    {
    }

    explicit IdentifierNode(std::string&& value)
        : Node(servedType())
        , m_value(std::move(value))
    {
    }

    ~IdentifierNode() override = default;
    void setType(Lexer::TokenType type) { m_type = type; }

    Lexer::TokenType type() const { return m_type; }
    const std::string& value() const { return m_value; }

    static NodeType servedType() { return Identifier; }

private:
    std::string m_value {};
    Lexer::TokenType m_type;
};

}