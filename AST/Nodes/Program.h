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

    ProgramNode(const std::vector<Node*>& nodes)
        : Node(servedType())
        , m_nodes(nodes)
    {
    }

    ProgramNode(std::vector<Node*>&& nodes)
        : Node(servedType())
        , m_nodes(std::move(nodes))
    {
    }

    ~ProgramNode() override = default;

    const std::vector<Node*>& nodes() const { return m_nodes; }

    static NodeType servedType() { return Program; }

private:
    std::vector<Node*> m_nodes {};
};

}
