#include "Parser.h"
#include "../AST/Nodes/BinaryOperation.h"
#include "../AST/Nodes/IntConst.h"
#include "../Exceptions.h"
#include <iostream>
#include <vector>
#include <stdlib.h>

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

AST::Node* Parser::factor()
{
    // TODO: check for out of scope.

    auto token = m_tokens[m_passedTokens + 1];

    if (isConstant(token)) {
        auto factor = new AST::IntConstNode(atoi(token.lexeme().c_str()));
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

AST::Node* Parser::multiplyDivide()
{
    auto* root = factor();
    if (!root) {
        return NULL;
    }
    while (m_tokens[m_passedTokens + 1].type() == oneCC::Lexer::TokenType::Multiply || m_tokens[m_passedTokens + 1].type() == oneCC::Lexer::TokenType::Divide) {
        auto* new_root = new AST::BinaryOperationNode();
        new_root->setOperation(m_tokens[m_passedTokens + 1].type());

        m_passedTokens++;

        new_root->setChildren(root, factor());
        root = new_root;
    }

    return root;
}

AST::Node* Parser::sum()
{
    auto* root = multiplyDivide();
    if (!root) {
        throw oneCC::Exceptions::ParserError("binary operation \"+\" should have 2 operands");
    }

    while (m_tokens[m_passedTokens + 1].type() == oneCC::Lexer::TokenType::Plus) {
        auto* new_root = new AST::BinaryOperationNode();
        new_root->setOperation(m_tokens[m_passedTokens + 1].type());

        m_passedTokens++;

        new_root->setChildren(root, multiplyDivide());
        root = new_root;
    }
    return root;
}

}