#pragma once

#include "../Lexer/Token.h"
#include <string>
#include <vector>
 
namespace oneCC::AST {

enum NodeType {
    Const,
    Identifier,
    Type,

    UnaryOperation,
    BinaryOperation,
    TernaryOperation,
    FunctionCallExpression,

    IfStatement,
    WhileStatement,
    ReturnStatement,
    BlockStatement,

    Function,
};

class Node {
public:
    const NodeType& type() const { return m_type; }
    virtual ~Node() = default;
protected:
    Node(NodeType type) : m_type(type) {}

private:
    NodeType m_type;
};

}