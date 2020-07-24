#pragma once
#include "../ASTNode.h"

namespace oneCC::AST {

class IntConstNode : public Expression {
//TODO: may be we should rename in to ConstNode, since it has a type()
public:
    IntConstNode()
        : Expression(servedType())
    {
    }

    IntConstNode(int value)
        : Expression(servedType())
        , m_value(value)
    {
    }

    virtual ~IntConstNode() = default;

    int value() const { return m_value; }

    static NodeType servedType() { return Const; }

private:
    int m_value;
};

}