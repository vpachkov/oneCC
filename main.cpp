#include "Lexer/Lexer.h"
#include <iostream>
#include "Utils/Utils.h"

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
    return 0;
}