#pragma once
#include "../ASTNode.h"

namespace oneCC::AST {

class IntConstNode : public Node {
//TODO: may be we should rename in to ConstNode, since it has a type()
public:
    IntConstNode()
        : Node(servedType())
    {
    }

    IntConstNode(int value)
        : Node(servedType())
        , m_value(value)
    {
    }

    virtual ~IntConstNode() = default;

    int value() const { return m_value; }
    void setType(Lexer::TokenType type) { m_type = type; } // not sure if it will be used

    Lexer::TokenType type() const {return m_type ; }

    static NodeType servedType() { return Const; }

private:
    int m_value;
    Lexer::TokenType m_type;
};

}