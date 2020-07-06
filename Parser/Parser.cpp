#include "Parser.h"
#include "../AST/Nodes/BinaryOperation.h"
#include "../AST/Nodes/IntConst.h"
#include "../Exceptions.h"
#include <iostream>
#include <stdlib.h>
#include <vector>

namespace oneCC::Parser {

Parser::Parser(std::unique_ptr<Lexer::Lexer> lexer)
    : m_lexer(std::move(lexer))
{
    m_lexer->tokinizeFile();
}

bool Parser::isConstant(oneCC::Lexer::Token& token)
{
    return token.type() == oneCC::Lexer::TokenType::IntConst || token.type() == oneCC::Lexer::TokenType::StringConst;
}

bool Parser::isType(oneCC::Lexer::Token& token)
{
    return token.type() == oneCC::Lexer::TokenType::TypeInt || token.type() == oneCC::Lexer::TokenType::TypeFloat;
}

AST::Node* Parser::factor()
{
    auto token = m_lexer->lookupToken();

    if (isConstant(token)) {
        auto factor = new AST::IntConstNode(atoi(token.lexeme().c_str()));
        m_lexer->eatToken();
        return factor;
    }

    if (token.type() == oneCC::Lexer::TokenType::OpenRoundBracket) {
        m_lexer->eatToken(); // Eats open bracket, go ahead.
        auto* expr = sum();
        if (m_lexer->lookupToken().type() == oneCC::Lexer::TokenType::CloseRoundBracket) {
            m_lexer->eatToken();
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
    while (m_lexer->lookupToken().type() == oneCC::Lexer::TokenType::Multiply || m_lexer->lookupToken().type() == oneCC::Lexer::TokenType::Divide) {
        auto* new_root = new AST::BinaryOperationNode();
        new_root->setOperation(m_lexer->lookupToken().type());
        m_lexer->eatToken();
        new_root->setChildren(root, factor());
        root = new_root;
    }

    return root;
}

AST::Node* Parser::sum()
{
    auto* root = multiplyDivide();
    if (!root) {
        // throw oneCC::Exceptions::ParserError("binary operation \"+\" should have 2 operands");
        return NULL;
    }

    while (m_lexer->lookupToken().type() == oneCC::Lexer::TokenType::Plus) {
        auto* new_root = new AST::BinaryOperationNode();
        new_root->setOperation(m_lexer->lookupToken().type());
        m_lexer->eatToken();
        new_root->setChildren(root, multiplyDivide());
        root = new_root;
    }
    return root;
}



GeneralExpression* Parser::createInt()
{
    // TODO: check for out of scope.

    auto type = m_tokens[m_passedTokens + 1];

    if (isType(type)) {
        auto* root = new GeneralExpression();
        root->expressionType = ExpressionType::TernaryOperaion;
        root->operation = oneCC::Lexer::TokenType::Assign;

        auto identifier = m_tokens[m_passedTokens + 2];

        if (identifier.type() != oneCC::Lexer::Identifier) {
            throw oneCC::Exceptions::ParserError("create int operation should have identifier");
        }

        auto expression = m_tokens[m_passedTokens + 3];

        auto* left = new GeneralExpression();
        left->constToken = type;
        left->expressionType = ExpressionType::Type;

        auto* middle = new GeneralExpression();
        middle->constToken = identifier;
        middle->expressionType = ExpressionType::Identifier;

        m_passedTokens += 3;

        root->operands = { left, middle, sum() };

        if (m_tokens[m_passedTokens + 1].type() != oneCC::Lexer::TokenType::EndOfStatement ) {
            throw oneCC::Exceptions::ParserError("Assign operation should have \";\"");
        }

        return root;

    }

    return NULL;
}

}