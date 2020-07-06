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
    index = -1; // starts reading tokens from the beginning
}

bool Parser::isConstant(oneCC::Lexer::Token& token){
    return token.type() == oneCC::Lexer::TokenType::IntConst ||
           token.type() == oneCC::Lexer::TokenType::StringConst;
}

GeneralExpression* Parser::factor() {
    // todo: check for out of scope

    auto token = m_tokens[index+1];

    if (isConstant(token)) {
        auto factor = new GeneralExpression();
        factor->expressionType = oneCC::Parser::ExpressionType::Const;
        factor->constToken = token;
        index++;
        return factor;
    }

    if (token.type() == oneCC::Lexer::TokenType::OpenRoundBracket) {
        index++; // eat open bracket, go ahead
        auto* expr = sum();
        if (m_tokens[index+1].type() == oneCC::Lexer::TokenType::CloseRoundBracket){
            index++;
            return expr;
        }
    }

    return NULL;
}

GeneralExpression* Parser::multiplyDivide() {
    GeneralExpression* root = factor();
    if (!root) {
        return NULL;
    }
    while (m_tokens[index+1].type() == oneCC::Lexer::TokenType::Multiply || m_tokens[index+1].type() == oneCC::Lexer::TokenType::Divide) {
        auto* new_root = new GeneralExpression();
        new_root->expressionType = ExpressionType::BinaryOperaion;
        new_root->operation = m_tokens[index+1].type();

        index++;

        new_root->operands = { root, factor() };
        root = new_root;
    }

    return root;
}

GeneralExpression* Parser::sum() {
    auto* root = multiplyDivide();
    if (!root) {
        throw oneCC::Exceptions::ParserError("binary operation \"+\" should have 2 operands");
    }

    while (m_tokens[index+1].type() == oneCC::Lexer::TokenType::Plus) {
        auto* new_root = new GeneralExpression();
        new_root->expressionType = ExpressionType::BinaryOperaion;
        new_root->operation = m_tokens[index+1].type();

        index++;

        auto* right_side = multiplyDivide();
        new_root->operands = { root, right_side };
        root = new_root;
    }
    return root;
}


}