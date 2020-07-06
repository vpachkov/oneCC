#pragma once
#include "../ASTNode.h"

namespace oneCC::AST {

class TypeNode : public Node {
//TODO: (Token.h) divide tokens by groups
public:
    TypeNode(oneCC::Lexer::TokenType type)
            : Node(Type)
            , m_type(type) { }

    ~TypeNode() override = default;

    oneCC::Lexer::TokenType type() const { return m_type; }

private:
    oneCC::Lexer::TokenType m_type;
};

}