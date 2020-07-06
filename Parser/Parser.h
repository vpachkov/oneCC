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
    void parse();
    AST::Node* nextExpression(AST::Node* prevExpression = NULL);

    bool isConstant(oneCC::Lexer::Token& token);

    AST::Node* factor();
    AST::Node* multiplyDivide();
    AST::Node* sum();

private:
    std::unique_ptr<Lexer::Lexer> m_lexer;
};

}