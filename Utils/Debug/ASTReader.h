#pragma once
#include "../../Lexer/Token.h"
#include "../../AST/ASTNode.h"
#include "../../AST/Nodes/BinaryOperation.h"
#include "../../AST/Nodes/IntConst.h"
#include <iostream>
#include <cstdint>
#include <string>

namespace oneCC::Utils::Debug {

char tokenTypeToString(int tokenType);

//void outputExpression(oneCC::Parser::GeneralExpression* expr, int depth = 0)
//{
//    if (expr->type() == oneCC::AST::NodeType::Const) {
//        auto* ptr = dynamic_cast<oneCC::AST::IntConstNode*>(expr);
//        if (!ptr) {
//            return;
//        }
//    if (expr == NULL){
//        std::cout << std::string(depth * 2, ' ');
//        std::cout << "undefined";
//    }
//
//    if (expr->expressionType == oneCC::Parser::ExpressionType::Type ) {
//        std::cout << std::string(depth * 2, ' ');
//        std::cout << expr->constToken.lexeme();
//    }
//
//    if (expr->expressionType == oneCC::Parser::ExpressionType::Identifier) {
//        std::cout << std::string(depth * 2, ' ');
//        std::cout << expr->constToken.lexeme();
//    }
//
//    if (expr->expressionType == oneCC::Parser::ExpressionType::Const) {
//        std::cout << std::string(depth * 2, ' ');
//        std::cout << expr->constToken.lexeme();
//    }
//    if (expr->expressionType == oneCC::Parser::ExpressionType::BinaryOperaion) {
//        outputExpression(expr->operands[0], depth + 1);
//        std::cout << std::string(depth * 2, ' ');
//        std::cout << tokenTypeToString(expr->operation) << std::endl;
//        outputExpression(expr->operands[1], depth + 1);
//    }
//
//    if (expr->expressionType == oneCC::Parser::ExpressionType::TernaryOperaion) {
//        outputExpression(expr->operands[0], depth + 1);
//        std::cout << std::string(depth * 2, ' ');
//        std::cout << tokenTypeToString(expr->operation) << std::endl;
//        outputExpression(expr->operands[1], depth + 1);
//        outputExpression(expr->operands[2], depth + 1);
//    }
//
//    std::cout << std::endl;
//}
}