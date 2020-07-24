#include "Parser.h"
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
    m_err += " at ";
    m_err += std::to_string(m_lexer->lineIndex());
    m_err += ", ";
    m_err += std::to_string(m_lexer->lineOffset());
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

inline bool Parser::isBooleanOperation(const Lexer::Token &token)
{
    // TODO: add more operations
    return token.type() == Lexer::TokenType::Equal;
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
        auto* factor = expression();
        eatToken(Lexer::TokenType::CloseRoundBracket);
        return factor;
    }

    if (token.type() == Lexer::TokenType::Identifier && lookupToken(2).type() == Lexer::TokenType::OpenRoundBracket){
        return functionCall();
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

AST::Node* Parser::sum()
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

AST::Node* Parser::booleanOperation()
{
    auto* root = sum();
    checkNode(root);

    while (isBooleanOperation(lookupToken().type())) {
        auto* newNode = new AST::BinaryOperationNode();
        newNode->setOperation(lookupToken().type());

        m_lexer->skipToken();

        auto* rightSide = sum();
        checkNode(rightSide);

        newNode->setChildren(root, rightSide);
        root = newNode;
    }

    return root;

}

// entry point for expression (
//     will be easier to add new expressions
//     just change to new root here
// )
AST::Node* Parser::expression()
{
    return booleanOperation();
}

AST::Node* Parser::functionCall()
{
    auto funcName = lookupToken();
    eatToken(Lexer::TokenType::Identifier);
    eatToken(Lexer::TokenType::OpenRoundBracket);

    std::vector<AST::Node*> arguments;
    if (lookupToken().type() != Lexer::TokenType::CloseRoundBracket) {
        auto* res = expression();
        checkNode(res);
        arguments.push_back(res);
        while (lookupToken().type() == Lexer::TokenType::Comma) {
            eatToken(Lexer::TokenType::Comma);
            auto* res = expression();
            checkNode(res);
            arguments.push_back(res);
        }
    }

    eatToken(Lexer::TokenType::CloseRoundBracket);

    return new AST::FunctionCallNode(funcName.lexeme(), arguments);
}

// Statements
AST::Node* Parser::createInt()
{
    auto type = lookupToken();
    eatToken(Lexer::TokenType::TypeInt);
    auto identifier = lookupToken();
    eatToken(Lexer::TokenType::Identifier);
    eatToken(Lexer::TokenType::Assign);
    auto* parsedExpr = expression();
    checkNode(parsedExpr);
    eatToken(Lexer::TokenType::EndOfStatement);
    return new AST::TernaryOperationNode(new AST::TypeNode(type.type()), new AST::IdentifierNode(identifier.lexeme()), parsedExpr, Lexer::TokenType::Assign);
}

AST::Node* Parser::reassignInt()
{
    auto identifier = lookupToken();
    eatToken(Lexer::TokenType::Identifier);
    eatToken(Lexer::TokenType::Assign);
    auto* parsedExpr = expression();
    checkNode(parsedExpr);
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
        checkNode(expr);
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
        checkNode(child);
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

AST::Node* Parser::callFunctionStatement()
{
    auto* funcCall = functionCall();
    eatToken(Lexer::TokenType::EndOfStatement);
    return funcCall;
}

AST::Node* Parser::statement(AST::Node* function)
{
    auto nextToken = lookupToken();

    if (isType(nextToken)) {
        // Since we are in statment, we expect only var delcs.
        return createInt();
    } else if (nextToken.type() == Lexer::TokenType::Identifier && lookupToken(2).type() == Lexer::TokenType::Assign) {
        return reassignInt();
    } else if (nextToken.type() == Lexer::TokenType::Identifier) {
        return callFunctionStatement();
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

AST::Node* Parser::declareFunctionArguments() {
    auto type = lookupToken();
    eatToken(Lexer::TokenType::TypeInt);
    auto varName = lookupToken();
    eatToken(Lexer::TokenType::Identifier);
    //TODO: where's createInt()? Consider moving it back here

    AST::Node* expr = NULL;
    if (lookupToken().type() == Lexer::TokenType::Assign) {
        eatToken(Lexer::TokenType::Assign);
        expr = expression();
    }
    return new AST::FunctionArgumentNode(new AST::IdentifierNode(varName.lexeme(), type.type()), expr);
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
        auto functionNode = new AST::FunctionNode(new AST::IdentifierNode(funcName.lexeme(), type.type()), arguments, NULL);
        auto blockStat = blockStatement(functionNode);
        checkNode(blockStat);
        functionNode->setStatement(blockStat);
        return functionNode;
    }
}

AST::Node* Parser::program()
{
    std::vector<AST::Node*> nodes;
    while (lookupToken().type() != Lexer::TokenType::EndOfFile) {
        AST::Node* node = NULL;
        if (isType(lookupToken().type())) {
            if (lookupToken(3).type() == Lexer::TokenType::OpenRoundBracket) {
                node = defineFunction();
            } else {
                node = createInt();
            }
        } else if (lookupToken().type() == Lexer::TokenType::Identifier) {
            node = reassignInt();
        }
        checkNode(node);
        nodes.push_back(node);
    }

    return new AST::ProgramNode(nodes);
}

// Entry point
AST::Node* Parser::parse()
{
    auto* root = program();
    if (!root) [[unlikely]] {
        throw oneCC::Exceptions::ParserError(m_err.c_str());
    }
    return root;
}

}