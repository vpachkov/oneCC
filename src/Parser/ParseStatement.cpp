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
#include "Defines.h"
#include "Parser.h"
#include <iostream>
#include <stdlib.h>
#include <vector>

namespace oneCC::Parser {

AST::Node* Parser::createIntStatement()
{
    auto type = lookupToken();
    eatToken(Lexer::TokenType::TypeInt);
    auto identifier = lookupToken();
    eatToken(Lexer::TokenType::Identifier);
    eatToken(Lexer::TokenType::Assign);
    auto* parsedExpr = expression();
    softAssertNode(parsedExpr);
    eatToken(Lexer::TokenType::EndOfStatement);
    return new AST::TernaryOperationNode(new AST::TypeNode(type.type()), new AST::IdentifierNode(identifier.lexeme()), parsedExpr, Lexer::TokenType::Assign);
}

AST::Node* Parser::reassignIntStatement()
{
    auto identifier = lookupToken();
    eatToken(Lexer::TokenType::Identifier);
    eatToken(Lexer::TokenType::Assign);
    auto* parsedExpr = expression();
    softAssertNode(parsedExpr);
    eatToken(Lexer::TokenType::EndOfStatement);
    return new AST::BinaryOperationNode(new AST::IdentifierNode(identifier.lexeme()), parsedExpr, Lexer::TokenType::Assign);
}

AST::Node* Parser::ifStatement(AST::Node* function)
{
    auto ifToken = lookupToken();

    if (ifToken.type() == Lexer::TokenType::If) {
        eatToken(Lexer::TokenType::If);
        eatToken(Lexer::TokenType::OpenRoundBracket);

        auto expr = expression();

        //TODO: Checking only returns NULL (better to throw an exception here)
        softAssertNode(expr);
        eatToken(Lexer::TokenType::CloseRoundBracket);

        auto trueStatement = statement(function);

        auto elseToken = lookupToken();
        if (elseToken.type() == Lexer::TokenType::Else) {
            eatToken(Lexer::TokenType::Else);
            auto falseStatement = statement(function);
            return new AST::IfStatementNode(expr, trueStatement, falseStatement);
        }
        return new AST::IfStatementNode(expr, trueStatement, NULL);
    }

    return NULL;
}

AST::Node* Parser::whileStatement(AST::Node* function)
{
    auto whileToken = lookupToken();
    if (whileToken.type() == Lexer::TokenType::While) {
        eatToken(Lexer::TokenType::While);
        eatToken(Lexer::TokenType::OpenRoundBracket);

        auto expr = expression();

        eatToken(Lexer::TokenType::CloseRoundBracket);
        eatToken(Lexer::TokenType::OpenCurlyBracket);

        auto stat = statement(function);

        eatToken(Lexer::TokenType::CloseCurlyBracket);

        return new AST::WhileStatementNode(expr, stat);
    }

    return NULL;
}

AST::Node* Parser::blockStatement(AST::Node* function)
{
    std::vector<AST::Node*> statements;

    eatToken(Lexer::TokenType::OpenCurlyBracket);

    while (lookupToken().type() != Lexer::TokenType::CloseCurlyBracket) {
        auto* child = statement(function);
        softAssertNode(child);
        statements.push_back(child);
    }

    eatToken(Lexer::TokenType::CloseCurlyBracket);

    return new AST::BlockStatementNode(statements);
}

AST::Node* Parser::returnStatement(AST::Node* function)
{
    // FIXME: may be used without return values (just return;)
    eatToken(Lexer::TokenType::Return);
    auto res = expression();
    eatToken(Lexer::TokenType::EndOfStatement);
    return new AST::ReturnStatementNode(res, function);
}

AST::Node* Parser::functionCallImpl()
{
    auto funcName = lookupToken();
    eatToken(Lexer::TokenType::Identifier);
    eatToken(Lexer::TokenType::OpenRoundBracket);

    std::vector<AST::Node*> arguments;
    if (lookupToken().type() != Lexer::TokenType::CloseRoundBracket) {
        auto* res = expression();
        softAssertNode(res);
        arguments.push_back(res);
        while (lookupToken().type() == Lexer::TokenType::Comma) {
            eatToken(Lexer::TokenType::Comma);
            auto* res = expression();
            softAssertNode(res);
            arguments.push_back(res);
        }
    }

    eatToken(Lexer::TokenType::CloseRoundBracket);

    return new AST::FunctionCallNode(funcName.lexeme(), arguments);
}

AST::Node* Parser::functionCallStatement()
{
    auto* funcCall = functionCallImpl();
    eatToken(Lexer::TokenType::EndOfStatement);
    return funcCall;
}

AST::Node* Parser::statement(AST::Node* function)
{
    auto nextToken = lookupToken();

    if (isType(nextToken)) {
        // Since we are in statment, we expect only var delcs.
        return createIntStatement();
    } else if (nextToken.type() == Lexer::TokenType::Identifier && lookupToken(2).type() == Lexer::TokenType::Assign) {
        return reassignIntStatement();
    } else if (nextToken.type() == Lexer::TokenType::Identifier) {
        return functionCallStatement();
    } else if (nextToken.type() == Lexer::TokenType::OpenCurlyBracket) {
        return blockStatement(function);
    } else if (nextToken.type() == Lexer::TokenType::Return) {
        return returnStatement(function);
    } else if (nextToken.type() == Lexer::TokenType::If) {
        return ifStatement(function);
    } else if (nextToken.type() == Lexer::TokenType::While) {
        return whileStatement(function);
    }
    return NULL;
}

}