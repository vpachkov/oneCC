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
    
    template<class T>
    std::vector<T*> statementsWithType() const
    {
        std::vector<T*> res;
        if (!std::is_base_of<AST::Node, T>::value) [[unlikely]] {
            return res;
        }

        for (auto node : m_statements) {
            if (node->type() == T::servedType()) {
                res.push_back(reinterpret_cast<T*>(node));
            }
        }
        return res;
    }

    static NodeType servedType() { return BlockStatement; }

private:
    std::vector<Node*> m_statements {};
};

}