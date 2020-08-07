#pragma once
#include "../ASTNode.h"
#include "../../Lexer/Token.h"
#include <string>
#include <utility>

namespace oneCC::AST {

class BooleanSnakeNode : public Node {
public:
    BooleanSnakeNode(Lexer::TokenType op)
        : Node(servedType())
        , m_op(op)
    {
    }

    explicit BooleanSnakeNode(const std::vector<Node*>& nodes, Lexer::TokenType op)
        : Node(servedType())
        , m_nodes(nodes)
        , m_op(op)
    {
    }

    explicit BooleanSnakeNode(std::vector<Node*>&& nodes, Lexer::TokenType op)
        : Node(servedType())
        , m_nodes(std::move(nodes))
        , m_op(op)
    {
    }

    ~BooleanSnakeNode() override = default;

    int add(Node* left)
    { 
        m_nodes.push_back(left);
        return 0;
    }

    const std::vector<Node*>& nodes() const { return m_nodes; }
    Lexer::TokenType operation() const { return m_op; }

    static NodeType servedType() { return BooleanSnake; }

private:
    std::vector<Node*> m_nodes {};
    Lexer::TokenType m_op;
};

}