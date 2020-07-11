#pragma once
#include "../ASTNode.h"

namespace oneCC::AST {

class IntConstNode : public Node {
public:
    IntConstNode()
        : Node(Const)
    {
    }

    IntConstNode(int value)
        : Node(Const)
        , m_value(value)
    {
    }

    virtual ~IntConstNode() = default;

    int value() const { return m_value; }

private:
    int m_value;
};

}