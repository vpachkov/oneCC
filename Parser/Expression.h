#pragma once
#include "../Lexer/Token.h"
#include <vector>
#include <string>
 
namespace oneCC::Parser {

enum ExpressionType {
    Const,
    BinaryOperaion,
    UnaryOperation,
};


class GeneralExpression {
public:
    ExpressionType expressionType;
    std::vector<GeneralExpression*> operands;
    oneCC::Lexer::TokenType operation;

    oneCC::Lexer::Token constToken;
};


}