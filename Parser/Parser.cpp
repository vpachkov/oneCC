#include "Parser.h"
#include "../AST/Nodes/BinaryOperation.h"
#include "../AST/Nodes/BlockStatement.h"
#include "../AST/Nodes/Function.h"
#include "../AST/Nodes/FunctionArgument.h"
#include "../AST/Nodes/FunctionCall.h"
#include "../AST/Nodes/Identifier.h"
#include "../AST/Nodes/IfStatement.h"
#include "../AST/Nodes/IntConst.h"
#include "../AST/Nodes/ReturnStatement.h"
#include "../AST/Nodes/TernaryOperation.h"
#include "../AST/Nodes/Type.h"
#include "../AST/Nodes/WhileStatement.h"
#include "../Exceptions.h"
#include "../Utils/Debug/ASTReader.h"
#include <iostream>
#include <stdlib.h>
#include <vector>

#define eatToken(...)                       \
    if (!tryToEatToken(__VA_ARGS__))        \
        [[unlikely]]                        \
        {                                   \
            generateErrorText(__VA_ARGS__); \
            return NULL;                    \
        }

#define checkNode(x)     \
    if (!x)              \
        [[unlikely]]     \
        {                \
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
    // TODO: need to support variables here

    auto token = lookupToken();

    if (isConstant(token)) {
        auto factor = new AST::IntConstNode(atoi(token.lexeme().c_str()));
        eatToken(Lexer::TokenType::IntConst);
        return factor;
    }

    if (token.type() == Lexer::TokenType::OpenRoundBracket) {
        eatToken(Lexer::TokenType::OpenRoundBracket);
        auto* factor = expr();
        eatToken(Lexer::TokenType::CloseRoundBracket);
        return factor;
    }

    if (token.type() == Lexer::TokenType::Identifier) {
        auto factor = new AST::IdentifierNode(token.lexeme());
        eatToken(Lexer::TokenType::Identifier);
        return factor;
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

        eatToken({ Lexer::TokenType::Multiply, Lexer::TokenType::Divide });

        auto* rightSide = factor();
        checkNode(rightSide);

        newNode->setChildren(root, rightSide);
        root = newNode;
    }

    return root;
}

AST::Node* Parser::expr()
{
    auto* root = multiplyDivide();
    checkNode(root);

    while (lookupToken().type() == Lexer::TokenType::Plus || lookupToken().type() == Lexer::TokenType::Minus) {
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
    eatToken(Lexer::TokenType::TypeInt);
    auto identifier = lookupToken();
    eatToken(Lexer::TokenType::Identifier);
    eatToken(Lexer::TokenType::Assign);
    auto* parsedExpr = expr();
    checkNode(parsedExpr);
    eatToken(Lexer::TokenType::EndOfStatement);
    return new AST::TernaryOperationNode(new AST::TypeNode(type.type()), new AST::IdentifierNode(identifier.lexeme()), parsedExpr, Lexer::TokenType::Assign);
}

AST::Node* Parser::functionCall()
{
    auto funcName = lookupToken();
    eatToken(Lexer::TokenType::Identifier);
    eatToken(Lexer::TokenType::OpenRoundBracket);

    std::vector<AST::Node*> arguments;
    if (lookupToken().type() != Lexer::TokenType::CloseRoundBracket) {
        auto* res = expr();
        checkNode(res);
        arguments.push_back(res);
        while (lookupToken().type() == Lexer::TokenType::Comma) {
            eatToken(Lexer::TokenType::Comma);
            auto* res = expr();
            checkNode(res);
            arguments.push_back(res);
        }
    }

    eatToken(Lexer::TokenType::CloseRoundBracket);
    eatToken(Lexer::TokenType::EndOfStatement);

    return new AST::FunctionCallNode(new AST::IdentifierNode(funcName.lexeme()), arguments);
}

AST::Node* Parser:: expression()
{
    auto token = lookupToken();

    switch (token.type()) {
    case Lexer::TokenType::TypeInt: {
        return createInt();
    }
    case Lexer::TokenType::Identifier: {
        // TODO: need to add variables in expr(), then at first, try to parse expr() here
        return functionCall();
    }
    }

    //TODO: add support for other expressions

    return NULL;
}

// Statements
AST::Node* Parser::ifStatement()
{
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
        if (elseToken.type() == Lexer::TokenType::Else) {
            auto falseStatement = statement();
            return new AST::IfStatementNode(expr, trueStatement, falseStatement);
        }
        return new AST::IfStatementNode(expr, trueStatement, NULL);
    }

    return NULL;
}

AST::Node* Parser::whileStatement()
{
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

AST::Node* Parser::blockStatement()
{
    std::vector<AST::Node*> statements;

    eatToken(Lexer::TokenType::OpenCurlyBracket);

    while (lookupToken().type() != Lexer::TokenType::CloseCurlyBracket) {
        auto* child = statement();
        checkNode(child);
        statements.push_back(child);
    }

    eatToken(Lexer::TokenType::CloseCurlyBracket);

    return new AST::BlockStatementNode(statements);
}

AST::Node* Parser::returnStatement()
{
    // FIXME: may be used without return values (just return;)
    eatToken(Lexer::TokenType::Return);
    auto res = expr();
    eatToken(Lexer::TokenType::EndOfStatement);
    return new AST::ReturnStatementNode(res);
}

AST::Node* Parser::statement()
{
    auto nextToken = lookupToken();

    if (isType(nextToken)) {
        // Since we are in statment, we expect only var delcs.
        return createInt();
    } else if (nextToken.type() == Lexer::TokenType::OpenCurlyBracket) {
        return blockStatement();
    } else if (nextToken.type() == Lexer::TokenType::Return) {
        return returnStatement();
    } else if (nextToken.type() == Lexer::TokenType::Identifier) {
        return functionCall();
    } 
    // else if (nextToken.type() == Lexer::TokenType::If) {
    //     return blockStatement();
    // } else if (nextToken.type() == Lexer::TokenType::OpenCurlyBracket) {
    //     return blockStatement();
    // } 
    return NULL;
}

AST::Node* Parser::declareFunctionArguments() {
    auto type = lookupToken();
    eatToken(Lexer::TokenType::TypeInt);
    auto varName = lookupToken();
    eatToken(Lexer::TokenType::Identifier);
    return new AST::FunctionArgumentNode(type.type(), varName.lexeme());
}

AST::Node* Parser::defineFunction()
{
    // FIXME: Now we eat only int
    auto type = lookupToken();
    eatToken(Lexer::TokenType::TypeInt);
    auto funcName = lookupToken();
    eatToken(Lexer::TokenType::Identifier);
    eatToken(Lexer::TokenType::OpenRoundBracket);

    // Eating args
    std::vector<AST::Node*> arguments;
    if (isType(lookupToken())) {
        // TODO: Make it cleaner.
        auto* argDecl = declareFunctionArguments();
        checkNode(argDecl);
        arguments.push_back(argDecl);
        while (lookupToken().type() == Lexer::TokenType::Comma) {
            eatToken(Lexer::TokenType::Comma);
            auto* argDecl = declareFunctionArguments();
            checkNode(argDecl);
            arguments.push_back(argDecl);
        }
    }

    eatToken(Lexer::TokenType::CloseRoundBracket);

    if (lookupToken().type() == Lexer::TokenType::EndOfStatement) {
        // FIXME: Add support for function declaration
        return NULL;
    } else {
        auto blockStat = blockStatement();
        checkNode(blockStat);
        return new AST::FunctionNode(new AST::TypeNode(type.type()), new AST::IdentifierNode(funcName.lexeme()), arguments, blockStat);
    }
}

// Entry point
AST::Node* Parser::parse()
{
    auto* root = defineFunction();
    if (!root) [[unlikely]] {
        throw oneCC::Exceptions::ParserError(m_err.c_str());
    }
    return root;
}

}