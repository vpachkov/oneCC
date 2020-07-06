#pragma once
#include "../Lexer/Token.h"
#include "../AST/ASTNode.h"
#include <vector>

namespace oneCC::Parser {

class Parser {
public:
    Parser(std::vector<oneCC::Lexer::Token>& tokens);
    void parse();
    AST::Node* nextExpression(AST::Node* prevExpression = NULL);

    bool isConstant(oneCC::Lexer::Token& token);

    AST::Node* factor();
    AST::Node* multiplyDivide();
    AST::Node* sum();

private:
    std::vector<oneCC::Lexer::Token> m_tokens;
    int m_passedTokens;
};

}