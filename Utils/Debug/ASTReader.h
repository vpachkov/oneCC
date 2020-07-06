#pragma once
#include "../../Lexer/Token.h"
#include "../../Parser/Expression.h"
#include <iostream>
#include <sstream>
#include <string>

namespace oneCC::Utils::Debug {

char tokenTypeToString(int tokenType){
    switch (tokenType)
    {
    case oneCC::Lexer::TokenType::Plus:
        return '+';
    case oneCC::Lexer::TokenType::Multiply:
        return '*';
    case oneCC::Lexer::TokenType::Divide:
        return '/';
    default:
        return '?';
    }
}
void outputExpression(oneCC::Parser::GeneralExpression* expr, int depth = 0)
{
    if (expr->expressionType == oneCC::Parser::ExpressionType::Const) {
        std::cout << std::string(depth * 2, ' ');
        std::cout << expr->constToken.lexeme();
    }
    if (expr->expressionType == oneCC::Parser::ExpressionType::BinaryOperaion) {
        outputExpression(expr->operands[0], depth + 1);
        std::cout << std::string(depth * 2, ' ');
        std::cout << tokenTypeToString(expr->operation) << std::endl;
        outputExpression(expr->operands[1], depth + 1);
    }

    std::cout << std::endl;
}
}