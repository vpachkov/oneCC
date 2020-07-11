#pragma once
#include "../ASTNode.h"

namespace oneCC::AST {

class BinaryOperationNode : public Node {
public:
    BinaryOperationNode()
        : Node(BinaryOperation)
    {
    }
    
    BinaryOperationNode(Node* left, Node* right, Lexer::TokenType operation)
        : Node(BinaryOperation)
        , m_left(left)
        , m_right(right)
        , m_operation(operation)
    {
    }

    virtual ~BinaryOperationNode() = default;

    void setChildren(Node* left, Node* right) { m_left = left, m_right = right; }
    void setLeftChild(Node* left) { m_left = left; }
    void setRightChild(Node* right) { m_right = right; }
    void setOperation(Lexer::TokenType operation) { m_operation = operation; }

    Node* leftChild() const { return m_left; }
    Node* rightChild() const { return m_right; }
    Lexer::TokenType operation() const { return m_operation; }

private:
    Node* m_left;
    Node* m_right;
    Lexer::TokenType m_operation;
};

}