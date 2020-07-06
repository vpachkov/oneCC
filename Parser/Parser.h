#pragma once
#include "../Lexer/Token.h"
#include "Expression.h"
#include <vector>

namespace oneCC::Parser {

class Parser {
public:
    Parser(std::vector<oneCC::Lexer::Token>& tokens);
    void parse();
    GeneralExpression* nextExpression(GeneralExpression* prevExpression = NULL);

    bool isConstant(oneCC::Lexer::Token& token);

    GeneralExpression* factor();
    GeneralExpression* multiplyDivide();
    GeneralExpression* sum();

private:
    std::vector<oneCC::Lexer::Token> m_tokens;

    int index;
};

}