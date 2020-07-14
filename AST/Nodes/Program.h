#pragma once
#include "../ASTNode.h"
#include <utility>
#include <vector>

namespace oneCC::AST {

class ProgramNode : public Node {
public:
    ProgramNode()
        : Node(servedType())
    {
    }

    ProgramNode(const std::vector<Node*>& funcs)
        : Node(servedType())
        , m_funcs(funcs)
    {
    }

    ProgramNode(std::vector<Node*>&& funcs)
        : Node(servedType())
        , m_funcs(std::move(funcs))
    {
    }

    ~ProgramNode() override = default;

    const std::vector<Node*>& funcs() const { return m_funcs; }

    static NodeType servedType() { return Program; }

private:
    std::vector<Node*> m_funcs {};
};

}
