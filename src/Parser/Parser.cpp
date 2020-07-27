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
#include "Defines.h"
#include <iostream>
#include <stdlib.h>
#include <vector>

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

    m_err += "\nBut found: ";
    m_err += oneCC::ASTUtils::Visualizer::tokenTypeToString(lookupToken(-1).type());
}

void Parser::generateErrorText(const std::vector<Lexer::TokenType>& tokenTypes)
{
    m_err = "Was expected symbols: ";
    for (auto tokenType : tokenTypes) {
        m_err += oneCC::ASTUtils::Visualizer::tokenTypeToString(tokenType);
        m_err += " ";
    }
}

bool Parser::isConstant(Lexer::Token& token)
{
    return token.type() == Lexer::TokenType::IntConst || token.type() == Lexer::TokenType::StringConst;
}

bool Parser::isType(const Lexer::Token& token)
{
    return token.type() == Lexer::TokenType::TypeInt || token.type() == Lexer::TokenType::TypeFloat;
}

Lexer::Token Parser::lookupToken(int offset)
{
    return m_lexer->lookupToken(offset);
}

Lexer::Token Parser::lookupToken()
{
    return m_lexer->lookupToken();
}

bool Parser::tryToEatToken(Lexer::TokenType tokenType)
{
    return m_lexer->skipToken().type() == tokenType;
}

bool Parser::tryToEatToken(const std::vector<Lexer::TokenType>& tokenTypes)
{
    auto activeTokenType = m_lexer->skipToken().type();
    for (auto tokenType : tokenTypes) {
        if (activeTokenType == tokenType) {
            return true;
        }
    }
    return false;
}

AST::Node* Parser::program()
{
    std::vector<AST::Node*> nodes;
    while (lookupToken().type() != Lexer::TokenType::EndOfFile) {
        AST::Node* node = NULL;
        if (isType(lookupToken().type())) {
            if (lookupToken(3).type() == Lexer::TokenType::OpenRoundBracket) {
                node = declareFunction();
            } else {
                node = createIntStatement();
            }
        } else if (lookupToken().type() == Lexer::TokenType::Identifier) {
            node = reassignIntStatement();
        }
        softAssertNode(node);
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