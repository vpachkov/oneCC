#pragma once
#include "../AST/ASTNode.h"
#include "../AST/Nodes/FunctionArgument.h"
#include "../Lexer/Lexer.h"
#include "../Lexer/Token.h"
#include <memory>
#include <vector>

namespace oneCC::Parser {

class Parser {
public:
    explicit Parser(std::unique_ptr<Lexer::Lexer> lexer);

    bool isConstant(Lexer::Token& token);
    bool isType(const Lexer::Token& token);
    bool isBooleanOperation(const Lexer::Token& token);

    AST::Node* parse();

private:
    Lexer::Token lookupToken(int offset);
    Lexer::Token lookupToken();

    bool tryToEatToken(Lexer::TokenType tokenType);
    bool tryToEatToken(const std::vector<Lexer::TokenType>& tokenTypes);

    AST::Node* factor();
    AST::Node* multiplyDivide();
    AST::Node* sumMinus();
    AST::Node* booleanOperation();
    AST::Node* expression();

    AST::Node* functionCallImpl();

    AST::Node* createIntStatement();
    AST::Node* reassignIntStatement();
    AST::Node* ifStatement(AST::Node* function = NULL);
    AST::Node* whileStatement(AST::Node* function = NULL);
    AST::Node* blockStatement(AST::Node* function = NULL);
    AST::Node* returnStatement(AST::Node* function = NULL);
    AST::Node* functionCallStatement();
    AST::Node* statement(AST::Node* function = NULL);

    AST::FunctionArgumentNode* eatFunctionArgument();
    AST::Node* declareFunction();

    AST::Node* program();

    void generateErrorText(Lexer::TokenType tokenType);
    void generateErrorText(const std::vector<Lexer::TokenType>& tokenTypes);

    std::string m_err;
    std::unique_ptr<Lexer::Lexer> m_lexer;
};

}