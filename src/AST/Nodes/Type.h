#pragma once
#include "../ASTNode.h"

namespace oneCC::AST {

// TODO: (Token.h) divide tokens by groups
class TypeNode : public Node {
public:
    TypeNode(oneCC::Lexer::TokenType type)
        : Node(servedType())
        , m_type(type)
    {
    }

    ~TypeNode() override = default;

    Lexer::TokenType type() const { return m_type; }

    static NodeType servedType() { return Type; }

private:
    Lexer::TokenType m_type;
};

}