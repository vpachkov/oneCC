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
        throw oneCC::Exceptions::ParserError("binary operation \"+\" should have 2 operands");
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

}