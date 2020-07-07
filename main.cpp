#include "Lexer/Lexer.h"
#include <iostream>
#include <vector>
#include "Utils/Utils.h"
#include "Parser/Parser.h"
#include "Utils/Debug/ASTReader.h"

inline bool exists_test0 (const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}

int main()
{
    std::cout << exists_test0("Tests/Lexer/Data/lexer.txt");
    auto ifstreamPtr = std::make_unique<std::ifstream>("Tests/Lexer/Data/lexer.txt");
    auto lexer = oneCC::Lexer::Lexer(std::move(ifstreamPtr));

    try {
        lexer.tokinizeFile();
    } catch (std::exception& e) {
        std::cout << "\n" << e.what() << "\n";
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

    auto ifstreamPtr4Parser = std::make_unique<std::ifstream>("Tests/Parser/Data/test.txt");
    auto lexer4Parser = std::make_unique<oneCC::Lexer::Lexer>(std::move(ifstreamPtr4Parser));
    auto parser = oneCC::Parser::Parser(std::move(lexer4Parser));
    try {
        auto* root = parser.parse();
    } catch (std::exception& e) {
        std::cout << "\n" << e.what() << "\n";
        return 1;
    }
    return 0;
}
