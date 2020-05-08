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

    bool isFactor(oneCC::Lexer::Token& token);

    GeneralExpression* factor();
    GeneralExpression* sum();
    GeneralExpression* multiply();

private:
    std::vector<oneCC::Lexer::Token> m_tokens;

    int index;
};

}