#pragma once
#include "../ASTNode.h"
#include <string>
#include <utility>

namespace oneCC::AST {

class BlockStatementNode : public Node {
public:
    BlockStatementNode()
        : Node(servedType())
    {
    }

    explicit BlockStatementNode(const std::vector<Node*>& statements)
        : Node(servedType())
        , m_statements(statements)
    {
    }

    explicit BlockStatementNode(std::vector<Node*>&& statements)
        : Node(servedType())
        , m_statements(std::move(statements))
    {
    }

    ~BlockStatementNode() override = default;

    const std::vector<Node*>& statements() const { return m_statements; }
    std::vector<Node*> statementsWithType(NodeType type) const
    {
        std::vector<Node*> res;
        for (auto node : m_statements) {
            if (node->type() == type) {
                res.push_back(node);
            }
        }
        return res;
    }

    static NodeType servedType() { return BlockStatement; }

private:
    std::vector<Node*> m_statements {};
};

}