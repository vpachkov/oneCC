#pragma once
#include "../ASTNode.h"

namespace oneCC::AST {

// TODO: (Token.h) divide tokens by groups
class TypeNode : public Node {
public:
    TypeNode(oneCC::Lexer::TokenType type)
        : Node(Type)
        , m_type(type)
    {
    }

    ~TypeNode() override = default;

    Lexer::TokenType type() const { return m_type; }

private:
    Lexer::TokenType m_type;
};

}