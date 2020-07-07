#include "ASTReader.h"

namespace oneCC::Utils::Debug {

char tokenTypeToString(int tokenType)
{
    switch (tokenType) {
    case Lexer::TokenType::Plus:
        return '+';
    case Lexer::TokenType::Multiply:
        return '*';
    case Lexer::TokenType::Divide:
        return '/';
    case Lexer::TokenType::Assign:
        return '=';
    case Lexer::TokenType::OpenRoundBracket:
        return '(';
    case Lexer::TokenType::CloseRoundBracket:
        return ')';
    default:
        return '?';
    }
}

}