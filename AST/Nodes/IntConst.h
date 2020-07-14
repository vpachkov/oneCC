#pragma once
#include "../ASTNode.h"

namespace oneCC::AST {

class IntConstNode : public Node {
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

    static NodeType servedType() { return Const; }

private:
    int m_value;
};

}