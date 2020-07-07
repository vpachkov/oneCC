#include "Parser.h"
#include "../AST/Nodes/BinaryOperation.h"
#include "../AST/Nodes/TernaryOperaion.h"
#include "../AST/Nodes/IntConst.h"
#include "../AST/Nodes/Type.h"
#include "../AST/Nodes/Identifier.h"
#include "../Exceptions.h"
#include "../Utils/Debug/ASTReader.h"
#include <iostream>
#include <stdlib.h>
#include <vector>

#define eatToken(x) if (m_lexer->skipToken().type() != x) [[unlikely]] { \
    generateErrorText(x);\
    return NULL; \
}

#define checkNode(x) if (!x) [[unlikely]] { \
    return NULL; \
}

namespace oneCC::Parser {

Parser::Parser(std::unique_ptr<Lexer::Lexer> lexer)
    : m_lexer(std::move(lexer))
{
    m_lexer->tokinizeFile();
}

void Parser::generateErrorText(Lexer::TokenType tokenType)
{
    m_err = "Was expected symbol: ";
    m_err += Utils::Debug::tokenTypeToString(tokenType);
}

inline bool Parser::isConstant(Lexer::Token& token)
{
    return token.type() == Lexer::TokenType::IntConst || token.type() == Lexer::TokenType::StringConst;
}

inline bool Parser::isType(Lexer::Token& token)
{
    return token.type() == Lexer::TokenType::TypeInt || token.type() == Lexer::TokenType::TypeFloat;
}

inline Lexer::Token Parser::lookupToken(int offset)
{
    return m_lexer->lookupToken(offset);
}

inline Lexer::Token Parser::lookupToken()
{
    return m_lexer->lookupToken();
}

AST::Node* Parser::factor()
{
    auto token = lookupToken();

    if (isConstant(token)) {
        auto factor = new AST::IntConstNode(atoi(token.lexeme().c_str()));
        eatToken(Lexer::TokenType::IntConst);
        return factor;
    }

    if (token.type() == Lexer::TokenType::OpenRoundBracket) {
        eatToken(Lexer::TokenType::OpenRoundBracket);
        auto* expr = sum();
        eatToken(Lexer::TokenType::CloseRoundBracket);
        return expr;
    }

    return NULL;
}

AST::Node* Parser::multiplyDivide()
{
    auto* root = factor();
    checkNode(root);
    
    while (lookupToken().type() == Lexer::TokenType::Multiply || lookupToken().type() == Lexer::TokenType::Divide) {
        auto* newNode = new AST::BinaryOperationNode();
        newNode->setOperation(lookupToken().type());
        
        m_lexer->skipToken();
        
        auto* rightSide = factor();
        checkNode(rightSide);

        newNode->setChildren(root, rightSide);
        root = newNode;
    }

    return root;
}

AST::Node* Parser::sum()
{
    auto* root = multiplyDivide();
    checkNode(root);

    while (lookupToken().type() == Lexer::TokenType::Plus) {
        auto* newNode = new AST::BinaryOperationNode();
        newNode->setOperation(lookupToken().type());
        
        m_lexer->skipToken();

        auto* rightSide = multiplyDivide();
        checkNode(rightSide);

        newNode->setChildren(root, rightSide);
        root = newNode;
    }

    return root;
}

AST::Node* Parser::createInt()
{
    auto type = lookupToken();

    if (isType(type)) {
        eatToken(Lexer::TokenType::TypeInt);
        auto identifier = lookupToken();
        eatToken(Lexer::TokenType::Identifier);
        auto parsedSum = sum();
        checkNode(parsedSum);
        eatToken(Lexer::TokenType::EndOfStatement);
        return new AST::TernaryOperationNode(new AST::TypeNode(type.type()), new AST::IdentifierNode(identifier.lexeme()), parsedSum, Lexer::TokenType::Assign);
    }

    return NULL;
}


// Entry point
AST::Node* Parser::parse()
{
    auto* root = sum();
    if (!root) [[unlikely]] {
        throw oneCC::Exceptions::ParserError(m_err.c_str());
    }
    return root;
}

}