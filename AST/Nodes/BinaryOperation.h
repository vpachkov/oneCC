#include "../ASTNode.h"

namespace oneCC::AST {

class BinaryOperationNode : public Node {
public:
    BinaryOperationNode() : Node(BinaryOperaion) { }
    BinaryOperationNode(Node* left, Node* right, oneCC::Lexer::TokenType operation)
        : Node(BinaryOperaion)
        , m_left(left)
        , m_right(right)
        , m_operation(operation) { }

    virtual ~BinaryOperationNode() = default;

    void setChildren(Node* left, Node* right) { m_left = left, m_right = right; }
    void setLeftChild(Node* left) { m_left = left; }
    void setRightChild(Node* right) { m_right = right; }
    void setOperation(oneCC::Lexer::TokenType operation) { m_operation = operation; }

    Node* leftChild() { return m_left; }
    Node* rightChild() { return m_right; }
    oneCC::Lexer::TokenType operation() { return m_operation; }

private:
    Node* m_left;
    Node* m_right;
    oneCC::Lexer::TokenType m_operation;
};

}