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
#include "../Exceptions.h"
#include "../Utils/ASTReader/ASTReader.h"
#include "Parser.h"
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

#define softAssertNode(x) \
    if (!x)               \
        [[unlikely]]      \
        {                 \
            return NULL;  \
        }

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

// Entry point
AST::Node* Parser::expression()
{
    return booleanOperation();
}

}
