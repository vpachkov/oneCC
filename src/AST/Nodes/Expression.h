#pragma once
#include "../ASTNode.h"

namespace oneCC::AST {

class Expression : public Node {
using Node::Node;
public:
    void setExpressionType(Lexer::TokenType expressionType) { m_expressionType = expressionType; }
    Lexer::TokenType expressionType() const { return m_expressionType ; }

    void setResultRegister(int resultRegister) { m_resultRegister = resultRegister; }
    int resultRegister() const { return m_resultRegister ; }

protected:
    Expression(NodeType type, Lexer::TokenType expressionType) : Node(type), m_expressionType(expressionType) {}
    Lexer::TokenType m_expressionType;

    int m_resultRegister; // indicates which register keeps the result of an expression
};

}