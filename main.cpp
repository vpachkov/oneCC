#include "Lexer/Lexer.h"
#include <iostream>

int main()
{
    auto ifstreamPtr = std::make_shared<std::ifstream>("test.txt");
    auto lexer = oneCC::Lexer::Lexer(ifstreamPtr);
    for (;;) {
        auto token = lexer.nextToken();
        if (token.type() == oneCC::Lexer::TokenType::EndOfFile) {
            break;
        } else {
            std::cout << token.value() << " " << token.type() << "\n";
        }
    }
    return 0;
}