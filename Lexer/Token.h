#pragma once
#include <string>

namespace oneCC::Lexer {
enum TokenType {
    Identifier,
    Punct,
    ConstString,
    ConstChar,

    // Keywords
    If,

    // Binary Operations
    Bigger,
    Plus,
    Multiply,
    Divide,
    Equal,

    // Others
    EndOfFile,
    Error,

    // Types
    IntConst,
    FloatConst,
    StringConst,

    TypeInt,
    TypeFloat,

    // Brackets
    OpenRoundBracket,
    CloseRoundBracket,
    OpenSquareBracket,
    CloseSquareBracket,

    Assign,

    EndOfStatement,
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