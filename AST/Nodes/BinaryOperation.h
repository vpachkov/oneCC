#pragma once
#include "../ASTNode.h"

namespace oneCC::AST {

class BinaryOperationNode : public Node {
public:
    BinaryOperationNode()
        : Node(servedType())
    {
    }
    
    BinaryOperationNode(Node* left, Node* right, Lexer::TokenType operation)
        : Node(servedType())
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
    void setType(Lexer::TokenType type) { m_type = type; }

    Node* leftChild() const { return m_left; }
    Node* rightChild() const { return m_right; }
    Lexer::TokenType operation() const { return m_operation; }
    Lexer::TokenType type() const { return m_type; }

    static NodeType servedType() { return BinaryOperation; }

private:
    Node* m_left;
    Node* m_right;
    Lexer::TokenType m_operation;
    Lexer::TokenType m_type;
};

}