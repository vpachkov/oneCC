#include "Lexer/Lexer.h"
#include "Parser/Parser.h"
#include "Utils/Debug/ASTReader.h"
#include "Utils/Utils.h"
#include <iostream>
#include <vector>

inline bool exists_test0(const std::string& name)
{
    std::ifstream f(name.c_str());
    return f.good();
}

int main()
{
    auto ifstreamPtr = std::make_unique<std::ifstream>("Tests/Lexer/Data/assign_expression.txt");
    auto lexer = oneCC::Lexer::Lexer(std::move(ifstreamPtr));

    try {
        lexer.tokinizeFile();
    } catch (std::exception& e) {
        std::cout << "\n"
                  << e.what() << "\n";
        return 1;
    }
    for (;;) {
        auto token = lexer.skipToken();
        if (token.type() == oneCC::Lexer::TokenType::EndOfFile) {
            break;
        } else {
            std::cout << token.lexeme() << "(" << oneCC::Lexer::Token::typeToString(token) << ") ";
        }
    }
    std::cout << "\n\n";
    auto ifstreamPtr4Parser = std::make_unique<std::ifstream>("Tests/Lexer/Data/assign_expression.txt");
    auto lexer4Parser = std::make_unique<oneCC::Lexer::Lexer>(std::move(ifstreamPtr4Parser));

    //    try {
    //        lexer4Parser->tokinizeFile();
    //    } catch (std::exception& e) {
    //        std::cout << "\n" << e.what() << "\n";
    //        return 1;
    //    }

    //    for (;;) {
    //        auto token = lexer4Parser->skipToken();
    //        if (token.type() == oneCC::Lexer::TokenType::EndOfFile) {
    //            break;
    //        } else {
    //            std::cout << token.lexeme() << "(" << oneCC::Lexer::Token::typeToString(token) << ") ";
    //        }
    //    }
    //    std::cout << "\n\n";

    auto parser = oneCC::Parser::Parser(std::move(lexer4Parser));
    oneCC::AST::Node* root;
    try {
        root = parser.parse();
    } catch (std::exception& e) {
        std::cout << "\n" << e.what() << "\n";
        return 1;
    }

    auto viz = oneCC::ASTUtils::Visualizer();
    viz.genTreePng(root);

    return 0;
}
