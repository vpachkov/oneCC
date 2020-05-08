#pragma once
#include "../../Lexer/Token.h"
#include "../../Parser/Expression.h"
#include <iostream>
#include <sstream>
#include <string>

namespace oneCC::Utils::Debug {

char tokenTypeToString(int tokenType){
    std::cout << "fdsfdsf";
    switch (tokenType)
    {
    case oneCC::Lexer::TokenType::Plus:
        return '+';
    default:
        return '?';
    }
}
void outputExpression(oneCC::Parser::GeneralExpression* expr, int depth = 0)
{
    std::cout << std::string(' ', depth * 2);

    if (expr->expressionType == oneCC::Parser::ExpressionType::Const) {
        std::cout << "fdfsdfdssd";
        std::cout << expr->constToken.lexeme();
    }
    if (expr->expressionType == oneCC::Parser::ExpressionType::BinaryOperaion) {
        std::cout << "fdfsdfdssd";
        std::cout << tokenTypeToString(expr->operation);
        outputExpression(expr->operands[0], depth + 1);
        outputExpression(expr->operands[1], depth + 1);
    }

    std::cout << std::endl;
}
}