#pragma once
#include "../Lexer/Token.h"
#include <string>
#include <vector>
 
namespace oneCC::AST {

enum NodeType {
    Const,
    BinaryOperaion,
    UnaryOperation,
};

class Node {
public:
    NodeType type() const { return m_type; }
protected:
    Node(NodeType type) : m_type(type) {}
    virtual ~Node() = default;
private:
    NodeType m_type;
};

}