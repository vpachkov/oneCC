#pragma once
#include "../ASTNode.h"
#include <string>
#include <utility>

namespace oneCC::AST {

class BlockStatementNode : public Node {
public:
    BlockStatementNode()
        : Node(BlockStatement)
    {
    }

    explicit BlockStatementNode(const std::vector<Node*>& statements)
        : Node(BlockStatement)
        , m_statements(statements)
    {
    }
    
    explicit BlockStatementNode(std::vector<Node*>&& statements)
        : Node(BlockStatement)
        , m_statements(std::move(statements))
    {
    }

    ~BlockStatementNode() override = default;

    const std::vector<Node*>& statements() const { return m_statements; }

private:
    std::vector<Node*> m_statements {};
};

}