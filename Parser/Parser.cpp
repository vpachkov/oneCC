#include "Parser.h"
#include "../Exceptions.h"
#include "../Lexer/Token.h"
#include "Expression.h"
#include <iostream>
#include <vector>

namespace oneCC::Parser {

Parser::Parser(std::vector<oneCC::Lexer::Token>& tokens)
    : m_tokens(tokens)
    , m_passedTokens(-1)
{
}

bool Parser::isConstant(oneCC::Lexer::Token& token)
{
    return token.type() == oneCC::Lexer::TokenType::IntConst || token.type() == oneCC::Lexer::TokenType::StringConst;
}

GeneralExpression* Parser::factor()
{
    // TODO: check for out of scope.

    auto token = m_tokens[m_passedTokens + 1];

    if (isConstant(token)) {
        auto factor = new GeneralExpression();
        factor->expressionType = oneCC::Parser::ExpressionType::Const;
        factor->constToken = token;
        m_passedTokens++;
        return factor;
    }

    if (token.type() == oneCC::Lexer::TokenType::OpenRoundBracket) {
        m_passedTokens++; // Eats open bracket, go ahead.
        auto* expr = sum();
        if (m_tokens[m_passedTokens + 1].type() == oneCC::Lexer::TokenType::CloseRoundBracket) {
            m_passedTokens++;
            return expr;
        }
    }

    return NULL;
}

GeneralExpression* Parser::multiplyDivide()
{
    GeneralExpression* root = factor();
    if (!root) {
        return NULL;
    }
    while (m_tokens[m_passedTokens + 1].type() == oneCC::Lexer::TokenType::Multiply || m_tokens[m_passedTokens + 1].type() == oneCC::Lexer::TokenType::Divide) {
        auto* new_root = new GeneralExpression();
        new_root->expressionType = ExpressionType::BinaryOperaion;
        new_root->operation = m_tokens[m_passedTokens + 1].type();

        m_passedTokens++;

        new_root->operands = { root, factor() };
        root = new_root;
    }

    return root;
}

GeneralExpression* Parser::sum()
{
    auto* root = multiplyDivide();
    if (!root) {
        throw oneCC::Exceptions::ParserError("binary operation \"+\" should have 2 operands");
    }

    while (m_tokens[m_passedTokens + 1].type() == oneCC::Lexer::TokenType::Plus) {
        auto* new_root = new GeneralExpression();
        new_root->expressionType = ExpressionType::BinaryOperaion;
        new_root->operation = m_tokens[m_passedTokens + 1].type();

        m_passedTokens++;

        auto* right_side = multiplyDivide();
        new_root->operands = { root, right_side };
        root = new_root;
    }
    return root;
}

}