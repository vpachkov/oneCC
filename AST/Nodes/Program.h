#pragma once
#include "../ASTNode.h"
#include <utility>
#include <vector>

namespace oneCC::AST {

class ProgramNode : public Node {
public:
    ProgramNode()
        : Node(Program)
    {
    }

    ProgramNode(const std::vector<Node*>& funcs)
        : Node(Program)
        , m_funcs(funcs)
    {
    }

    ProgramNode(std::vector<Node*>&& funcs)
        : Node(Program)
        , m_funcs(std::move(funcs))
    {
    }

    ~ProgramNode() override = default;

    const std::vector<Node*>& funcs() const { return m_funcs; }

private:
    std::vector<Node*> m_funcs {};
};

}
