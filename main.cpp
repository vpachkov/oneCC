#include "Lexer/Lexer.h"
#include <iostream>
#include <vector>
#include "Utils/Utils.h"
#include "Utils/Debug/ASTReader.h"
#include "Parser/Parser.h"

int main()
{
    auto ifstreamPtr = std::make_shared<std::ifstream>("Tests/Lexer/Data/lexer.txt");
    auto lexer = oneCC::Lexer::Lexer(ifstreamPtr);
    for (;;) {
        oneCC::Lexer::Token token;
        try {
            token = lexer.nextToken();
        } catch (std::exception& e) {
            std::cout << "\n" << e.what() << "\n";
            return 1;
        }

        if (token.type() == oneCC::Lexer::TokenType::EndOfFile) {
            break;
        } else {
            std::cout << token.lexeme() << "(" << oneCC::Lexer::Token::typeToString(token) << ") ";
        }
    }
    std::cout << "\n\n";

    std::vector<oneCC::Lexer::Token> tokens = {
        oneCC::Lexer::Token("1", oneCC::Lexer::TokenType::IntConst),
        oneCC::Lexer::Token("+", oneCC::Lexer::TokenType::Plus),
        oneCC::Lexer::Token("1", oneCC::Lexer::TokenType::IntConst),
    };

    auto parser = oneCC::Parser::Parser(tokens);
    // oneCC::Utils::Debug::outputExpression(parser.sum());
    auto s = parser.sum();
    std::cout << s->operands[0]->constToken.lexeme();
    return 0;
}