#include "Token.h"
#include <string>

namespace oneCC::Lexer {
Token::Token(std::string lexeme, TokenType type)
    : m_lexeme(lexeme)
    , m_type(type)
{
}

Token::Token(const char* lexeme, TokenType type)
    : m_lexeme(lexeme)
    , m_type(type)
{
}

}