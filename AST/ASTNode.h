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
    FunctionArgument,

    Program,
};

class Node {
public:
    const NodeType& nodeType() const { return m_nodeType; }
    virtual ~Node() = default;
protected:
    Node(NodeType type) : m_nodeType(type) {}

private:
    NodeType m_nodeType;
};

}