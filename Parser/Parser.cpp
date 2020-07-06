#include "Parser.h"
#include "../AST/Nodes/BinaryOperation.h"
#include "../AST/Nodes/TernaryOperaion.h"
#include "../AST/Nodes/IntConst.h"
#include "../AST/Nodes/Type.h"
#include "../AST/Nodes/Identifier.h"
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



AST::Node* Parser::createInt()
{
    // TODO: check for out of scope.

    auto type = m_lexer->lookupToken();

    if (isType(type)) {

        auto identifier = m_lexer->lookupToken(1);

        if (identifier.type() != oneCC::Lexer::Identifier) {
            throw oneCC::Exceptions::ParserError("create int operation should have identifier");
        }

        m_lexer->eatToken(1);

        auto parsedSum = sum();

        if (m_lexer->lookupToken().type() != oneCC::Lexer::TokenType::EndOfStatement ) {
            throw oneCC::Exceptions::ParserError("Assign operation should have \";\"");
        }

        return new AST::TernaryOperationNode(
        new AST::TypeNode(type.type()),
        new AST::IdentifierNode(identifier.lexeme()),
        parsedSum,
        oneCC::Lexer::TokenType::Assign
        );

    }

    return NULL;
}

}