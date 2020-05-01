#include "Token.h"
#include <string>

namespace oneCC::Lexer {
Token::Token(std::string value, TokenType type)
    : m_value(value)
    , m_type(type)
{
}

Token::Token(const char* value, TokenType type)
    : m_value(value)
    , m_type(type)
{
}

}