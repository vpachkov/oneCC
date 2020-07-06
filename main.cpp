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
    auto ifstreamPtr = std::make_unique<std::ifstream>("Tests/Lexer/Data/lexer.txt");
    auto lexer = oneCC::Lexer::Lexer(std::move(ifstreamPtr));
    
    try {
        lexer.tokinizeFile();
    } catch (std::exception& e) {
        std::cout << "\n" << e.what() << "\n";
        return 1;
    }
    for (;;) {
        auto token = lexer.nextToken();
        if (token.type() == oneCC::Lexer::TokenType::EndOfFile) {
            break;
        } else {
            std::cout << token.lexeme() << "(" << oneCC::Lexer::Token::typeToString(token) << ") ";
        }
    }
    std::cout << "\n\n";

    std::vector<oneCC::Lexer::Token> tokens = {
        oneCC::Lexer::Token("(", oneCC::Lexer::TokenType::OpenRoundBracket),
        oneCC::Lexer::Token("1", oneCC::Lexer::TokenType::IntConst),
        oneCC::Lexer::Token("+", oneCC::Lexer::TokenType::Plus),
        oneCC::Lexer::Token("2", oneCC::Lexer::TokenType::IntConst),
        oneCC::Lexer::Token(")", oneCC::Lexer::TokenType::CloseRoundBracket),
        oneCC::Lexer::Token("*", oneCC::Lexer::TokenType::Multiply),
        oneCC::Lexer::Token("3", oneCC::Lexer::TokenType::IntConst),
        oneCC::Lexer::Token("/", oneCC::Lexer::TokenType::Divide),
        oneCC::Lexer::Token("4", oneCC::Lexer::TokenType::IntConst),
    };

    auto parser = oneCC::Parser::Parser(tokens);
    auto* root = parser.sum();
    oneCC::Utils::Debug::outputExpression(root);
    return 0;
}
