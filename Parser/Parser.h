#pragma once
#include "../Lexer/Lexer.h"
#include "../Lexer/Token.h"
#include "../AST/ASTNode.h"
#include <vector>
#include <memory>

namespace oneCC::Parser {

class Parser {
public:
    Parser(std::unique_ptr<Lexer::Lexer> lexer);
    AST::Node* nextExpression(AST::Node* prevExpression = NULL);

    bool isConstant(Lexer::Token& token);
    bool isType(Lexer::Token& token);

    AST::Node* parse();

private:
    Lexer::Token lookupToken(int offset);
    Lexer::Token lookupToken();

    bool tryToEatToken(Lexer::TokenType tokenType);
    bool tryToEatToken(std::vector<Lexer::TokenType> tokenTypes);

    AST::Node* factor();
    AST::Node* multiplyDivide();
    AST::Node* sum();

    AST::Node* typeInt();
    AST::Node* createInt();

    void generateErrorText(Lexer::TokenType tokenType);
    void generateErrorText(std::vector<Lexer::TokenType> tokenTypes);

    std::string m_err;
    std::unique_ptr<Lexer::Lexer> m_lexer;
};

}