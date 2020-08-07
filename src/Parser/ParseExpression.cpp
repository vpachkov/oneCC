#include "../AST/Nodes/BinaryOperation.h"
#include "../AST/Nodes/BlockStatement.h"
#include "../AST/Nodes/Function.h"
#include "../AST/Nodes/FunctionArgument.h"
#include "../AST/Nodes/FunctionCall.h"
#include "../AST/Nodes/Identifier.h"
#include "../AST/Nodes/IfStatement.h"
#include "../AST/Nodes/IntConst.h"
#include "../AST/Nodes/Program.h"
#include "../AST/Nodes/ReturnStatement.h"
#include "../AST/Nodes/TernaryOperation.h"
#include "../AST/Nodes/Type.h"
#include "../AST/Nodes/WhileStatement.h"
#include "../AST/Nodes/BooleanSnake.h"
#include "../Exceptions.h"
#include "../Utils/ASTReader/ASTReader.h"
#include "Defines.h"
#include "Parser.h"
#include <iostream>
#include <stdlib.h>
#include <vector>

namespace oneCC::Parser {

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
        auto* factor = expression();
        eatToken(Lexer::TokenType::CloseRoundBracket);
        return factor;
    }

    if (token.type() == Lexer::TokenType::Identifier && lookupToken(2).type() == Lexer::TokenType::OpenRoundBracket) {
        return functionCallImpl();
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
    softAssertNode(root);

    while (lookupToken().type() == Lexer::TokenType::Multiply || lookupToken().type() == Lexer::TokenType::Divide) {
        auto* newNode = new AST::BinaryOperationNode();
        newNode->setOperation(lookupToken().type());

        eatToken({ Lexer::TokenType::Multiply, Lexer::TokenType::Divide });

        auto* rightSide = factor();
        softAssertNode(rightSide);

        newNode->setChildren(root, rightSide);
        root = newNode;
    }

    return root;
}

AST::Node* Parser::sumMinus()
{
    auto* root = multiplyDivide();
    softAssertNode(root);

    while (lookupToken().type() == Lexer::TokenType::Plus || lookupToken().type() == Lexer::TokenType::Minus) {
        auto* newNode = new AST::BinaryOperationNode();
        newNode->setOperation(lookupToken().type());

        m_lexer->skipToken();

        auto* rightSide = multiplyDivide();
        softAssertNode(rightSide);

        newNode->setChildren(root, rightSide);
        root = newNode;
    }

    return root;
}

inline bool Parser::isBooleanOperation(const Lexer::Token& token)
{
    return Lexer::TokenType::_BooleanStart < token.type() && token.type() < Lexer::TokenType::_BooleanEnd;
}

AST::Node* Parser::booleanOperation()
{
    auto* root = sumMinus();
    softAssertNode(root);

    while (isBooleanOperation(lookupToken())) {
        auto* newNode = new AST::BinaryOperationNode();
        newNode->setOperation(lookupToken().type());

        m_lexer->skipToken();

        auto* rightSide = sumMinus();
        softAssertNode(rightSide);

        newNode->setChildren(root, rightSide);
        root = newNode;
    }

    return root;
}

// Boolean Snake is a sequence of booleanOperation
// Rule: booleanOperation repeate(&& or || booleanOperation)
// Example: a && v && c || a || b
AST::Node* Parser::booleanSnakeAnd()
{
    auto* root = booleanOperation();
    softAssertNode(root);

    if (lookupToken().type() != Lexer::TokenType::Or) {
        return root;
    }

    auto* snake = new AST::BooleanSnakeNode(Lexer::TokenType::Or);
    snake->add(root);

    while (lookupToken().type() == Lexer::TokenType::Or) {
        m_lexer->skipToken();

        auto* right = booleanOperation();
        softAssertNode(right);

        snake->add(right);
    }

    return snake;
}

AST::Node* Parser::booleanSnakeOr()
{
    auto* root = booleanSnakeAnd();
    softAssertNode(root);

    if (lookupToken().type() != Lexer::TokenType::And) {
        return root;
    }

    auto* snake = new AST::BooleanSnakeNode(Lexer::TokenType::And);
    snake->add(root);

    while (lookupToken().type() == Lexer::TokenType::And) {
        m_lexer->skipToken();

        auto* right = booleanOperation();
        softAssertNode(right);

        snake->add(right);
    }

    return snake;
}

// Entry point
AST::Node* Parser::expression()
{
    return booleanSnakeOr();
}

}
