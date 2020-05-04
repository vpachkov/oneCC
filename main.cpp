#include "Lexer/Lexer.h"
#include <iostream>

int main()
{
    auto ifstreamPtr = std::make_shared<std::ifstream>("Tests/Lexer/Data/lexer.txt");
    auto lexer = oneCC::Lexer::Lexer(ifstreamPtr);
    for (;;) {
        auto token = lexer.nextToken();
        if (token.type() == oneCC::Lexer::TokenType::EndOfFile) {
            break;
        } else if (token.type() == oneCC::Lexer::TokenType::Error) {
            std::cout << "Error parsing\n";
            return 1;
        } else {
            std::cout << token.lexeme() << " " << token.type() << "\n";
        }
    }
    return 0;
}