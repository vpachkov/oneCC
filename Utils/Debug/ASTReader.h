#pragma once
#include "../../Lexer/Token.h"
#include "../../AST/ASTNode.h"
#include "../../AST/Nodes/BinaryOperation.h"
#include "../../AST/Nodes/IntConst.h"
#include <iostream>
#include <cstdint>
#include <string>

namespace oneCC::Utils::Debug {

char tokenTypeToString(int tokenType)
{
    switch (tokenType) {
    case oneCC::Lexer::TokenType::Plus:
        return '+';
    case oneCC::Lexer::TokenType::Multiply:
        return '*';
    case oneCC::Lexer::TokenType::Divide:
        return '/';
    default:
        return '?';
    }
    
}
void outputExpression(oneCC::AST::Node* expr, int depth = 0)
{
    if (expr->type() == oneCC::AST::NodeType::Const) {
        auto* ptr = dynamic_cast<oneCC::AST::IntConstNode*>(expr);
        if (!ptr) {
            return;
        }
        std::cout << std::string(depth * 2, ' ');
        std::cout << ptr->value();
    }
    if (expr->type() == oneCC::AST::NodeType::BinaryOperaion) {
        auto* ptr = dynamic_cast<oneCC::AST::BinaryOperationNode*>(expr);
        if (!ptr) {
            return;
        }
        outputExpression(ptr->leftChild(), depth + 1);
        std::cout << std::string(depth * 2, ' ');
        std::cout << tokenTypeToString(ptr->operation()) << std::endl;
        outputExpression(ptr->rightChild(), depth + 1);
    }

    std::cout << std::endl;
}
}