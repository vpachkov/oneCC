#pragma once
#include <string>

namespace oneCC::Lexer {
enum TokenType {
    IntConst,
    FloatConst,
    Identifier,
    Punct,
    ConstString,
    ConstChar,

    // Keywords
    If,

    // Operations
    Bigger,

    // Others
    EndOfFile,
    Error,
};

class Token {
public:
    Token();
    Token(TokenType type);
    Token(const char* lexeme, TokenType type);
    Token(std::string lexeme, TokenType type);

    TokenType type() const { return m_type; }
    std::string lexeme() const { return m_lexeme; }

    static std::string typeToString(Token& tt);

private:
    std::string m_lexeme;
    TokenType m_type;
};
}