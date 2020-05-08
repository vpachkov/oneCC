#include "Parser.h"
#include "../Exceptions.h"
#include "../Lexer/Token.h"
#include "Expression.h"
#include <vector>
#include <iostream>

namespace oneCC::Parser {

Parser::Parser(std::vector<oneCC::Lexer::Token>& tokens)
{
    m_tokens = tokens;
    index = 0; // starts reading tokens from the beginning
}

bool Parser::isFactor(oneCC::Lexer::Token& token){
    return token.type() == oneCC::Lexer::TokenType::IntConst ||
           token.type() == oneCC::Lexer::TokenType::StringConst;
}

GeneralExpression* Parser::factor() {
    auto token = m_tokens[index];
    if (!isFactor(token)){
        throw oneCC::Exceptions::ParserError("expected factor");
    }
    auto factor = new GeneralExpression();
    factor->expressionType = oneCC::Parser::ExpressionType::Const;
    factor->constToken = token;
    return factor;
}

GeneralExpression* Parser::multiply() {
    GeneralExpression* root = factor();
    while (m_tokens[index].type() == oneCC::Lexer::TokenType::Multiply) {
        GeneralExpression* new_root = new GeneralExpression();
        new_root->expressionType = ExpressionType::BinaryOperaion;
        new_root->operation = m_tokens[index].type();
        index++;

        new_root->operands = {root, factor()};
        root = new_root;
    }

    return root;
}

GeneralExpression* Parser::sum() {
    GeneralExpression* root = factor();
    while (m_tokens[index].type() == oneCC::Lexer::TokenType::Plus) {
        GeneralExpression* new_root = new GeneralExpression();
        new_root->expressionType = ExpressionType::BinaryOperaion;
        new_root->operation = m_tokens[index].type();
        index++;

        new_root->operands = {root, factor()};
        root = new_root;
    }

    return root;
}

GeneralExpression* Parser::nextExpression(GeneralExpression* prevExpression)
{
    index++;
    const oneCC::Lexer::Token token = m_tokens[index];

    if (token.type() == oneCC::Lexer::TokenType::Plus) {
        if (prevExpression) {
            GeneralExpression* new_root = new GeneralExpression();
            new_root->expressionType = ExpressionType::BinaryOperaion;
            new_root->operation = token.type();
            GeneralExpression* rightSide = nextExpression();
            if (rightSide) {
                new_root->operands = { prevExpression, rightSide };
                return new_root;
            }
        }
        throw oneCC::Exceptions::ParserError("binary operation should have 2 operands");
    }

    if (token.type() == oneCC::Lexer::TokenType::IntConst) {
        GeneralExpression* expr = new GeneralExpression();
        expr->expressionType = ExpressionType::Const;
        expr->constToken = token;

        GeneralExpression* next
            = nextExpression(expr);
        if (next) {
            return next;
        }
        return expr;
    }

    if (token.type() == oneCC::Lexer::TokenType::Punct && token.lexeme() == "(") {
        return nextExpression();
    }

    if (token.type() == oneCC::Lexer::TokenType::Punct && token.lexeme() == ")") {
        return prevExpression;
    }

    return NULL;
}

}