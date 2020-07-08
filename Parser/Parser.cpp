#include "Parser.h"
#include "../AST/Nodes/BinaryOperation.h"
#include "../AST/Nodes/TernaryOperaion.h"
#include "../AST/Nodes/IntConst.h"
#include "../AST/Nodes/Type.h"
#include "../AST/Nodes/Identifier.h"
#include "../AST/Nodes/Function.h"
#include "../AST/Nodes/IfStatement.h"
#include "../AST/Nodes/WhileStatement.h"
#include "../AST/Nodes/ReturnStatement.h"
#include "../AST/Nodes/BlockStatement.h"
#include "../Exceptions.h"
#include "../Utils/Debug/ASTReader.h"
#include <iostream>
#include <stdlib.h>
#include <vector>

#define eatToken(...) if (!tryToEatToken(__VA_ARGS__)) [[unlikely]] { \
    generateErrorText(__VA_ARGS__);\
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
    m_err += oneCC::ASTUtils::Visualizer::tokenTypeToString(tokenType);
}

void Parser::generateErrorText(const std::vector<Lexer::TokenType>& tokenTypes)
{
    m_err = "Was expected symbols: ";
    for (auto tokenType : tokenTypes) {
        m_err += oneCC::ASTUtils::Visualizer::tokenTypeToString(tokenType);
        m_err += " ";
    }
}

inline bool Parser::isConstant(Lexer::Token& token)
{
    return token.type() == Lexer::TokenType::IntConst || token.type() == Lexer::TokenType::StringConst;
}

inline bool Parser::isType(const Lexer::Token& token)
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

inline bool Parser::tryToEatToken(Lexer::TokenType tokenType)
{
    return m_lexer->skipToken().type() == tokenType;
}

inline bool Parser::tryToEatToken(const std::vector<Lexer::TokenType>& tokenTypes)
{
    auto activeTokenType = m_lexer->skipToken().type();
    for (auto tokenType : tokenTypes) {
        if (activeTokenType == tokenType) {
            return true;
        }
    }
    return false;
}

// Expressions
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
        
        eatToken({Lexer::TokenType::Multiply, Lexer::TokenType::Divide});
        
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
        eatToken(Lexer::TokenType::Assign);
        auto parsedSum = sum();
        eatToken(Lexer::TokenType::EndOfStatement);
        return new AST::TernaryOperationNode(new AST::TypeNode(type.type()), new AST::IdentifierNode(identifier.lexeme()), parsedSum, Lexer::TokenType::Assign);
    }

    return NULL;
}

AST::Node* Parser::expression() {
    auto token = lookupToken();

    switch (token.type()) {
        case Lexer::TokenType::TypeInt: {
            return createInt();
        }
    }

    //TODO: add support for other expressions

    return NULL;

}

// Statements
AST::Node* Parser::ifStatement() {
    auto ifToken = lookupToken();

    if (ifToken.type() == Lexer::TokenType::If) {
        eatToken(Lexer::TokenType::If);
        eatToken(Lexer::TokenType::OpenRoundBracket);

        auto expr = expression();

        //TODO: Checking only returns NULL (better to throw an exception here)
        checkNode(expr);
        eatToken(Lexer::TokenType::CloseRoundBracket);

        auto trueStatement = statement();

        auto elseToken = lookupToken();
        if (elseToken.type() == Lexer::TokenType::Else){
            auto falseStatement = statement();
            return new AST::IfStatementNode(expr, trueStatement, falseStatement);
        }
        return new AST::IfStatementNode(expr, trueStatement , NULL);
    }

    return NULL;
}

AST::Node* Parser::whileStatement() {
    auto whileToken = lookupToken();
    if (whileToken.type() == Lexer::TokenType::While) {
        eatToken(Lexer::TokenType::While);
        eatToken(Lexer::TokenType::OpenRoundBracket);

        // TODO: Create isn't lowest expression
        auto expression = createInt();

        eatToken(Lexer::TokenType::CloseRoundBracket);
        eatToken(Lexer::TokenType::OpenCurlyBracket);

        auto stat = statement();

        eatToken(Lexer::TokenType::CloseCurlyBracket);

        return new AST::WhileStatementNode(expression, stat);
    }

    return NULL;
}

AST::Node* Parser::blockStatement() {
    std::vector<AST::Node*>statements;

    while (lookupToken().type() == Lexer::TokenType::OpenCurlyBracket) {
        eatToken(Lexer::TokenType::OpenCurlyBracket);
        statements.push_back(statement());
        eatToken(Lexer::TokenType::CloseCurlyBracket);
    }

    if (statements.empty()) {
        return NULL;
    }

    return new AST::BlockStatementNode(statements);
}

AST::Node* Parser::returnStatement() {
    if (lookupToken().type() == Lexer::TokenType::Return) {
        eatToken(Lexer::TokenType::Return);
        auto expr = expression();
        eatToken(Lexer::TokenType::EndOfStatement);

        return new AST::ReturnStatementNode(expr);
    }

    return NULL;
}

AST::Node* Parser::statement() {
    auto token = lookupToken();
    switch (token.type()) {
        case Lexer::TokenType::OpenCurlyBracket: {
            return blockStatement();
        }

        case Lexer::TokenType::If: {
            return ifStatement();
        }

        case Lexer::TokenType::While: {
            return whileStatement();
        }

        case Lexer::TokenType::Return: {
            return returnStatement();
        }

    }

    return NULL;

}

AST::Node* Parser::defineFunction() {
    auto type = lookupToken();

    if (isType(type)) {
        eatToken(Lexer::TokenType::TypeInt);
        auto identifier = lookupToken();
        eatToken(Lexer::TokenType::Identifier);
        eatToken(Lexer::TokenType::OpenRoundBracket);

        std::vector<AST::Node*> arguments;
        while (isType(lookupToken())) {
            arguments.push_back(expression());
            if (lookupToken().type() == Lexer::TokenType::Comma) {
                eatToken(Lexer::TokenType::Comma);
            }
            else if (lookupToken().type() != Lexer::TokenType::CloseRoundBracket) {
                //TODO: definitely should be an exception
                return NULL;
            }
        }

        eatToken(Lexer::TokenType::CloseRoundBracket);

        /* TODO: Function declarations should be taken in account
           int func(int a, int b);
        */

        auto blockStat = blockStatement();
        if (blockStat->type() != AST::BlockStatement){
            //TODO: exception
            return NULL;
        }

        return new AST::FunctionNode(new AST::TypeNode(type.type()), new AST::IdentifierNode(identifier.lexeme()), arguments, blockStat);
    }

    return NULL;
}

// Entry point
AST::Node* Parser::parse()
{
    auto* root = createInt();
    if (!root) [[unlikely]] {
        throw oneCC::Exceptions::ParserError(m_err.c_str());
    }
    return root;
}

}