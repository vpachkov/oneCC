#pragma once
#include <string>

namespace oneCC::Lexer {
enum TokenType {
    Identifier,
    Punct,
    ConstString,
    ConstChar,
    Comma,

    // Keywords
    If,
    Else,
    While,

    // Binary Operations
    Plus,
    Minus,
    Multiply,
    Divide,
    Equal,

    Bigger,

    // Others
    EndOfFile,

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
    OpenCurlyBracket,
    CloseCurlyBracket,

    Assign,

    EndOfStatement,

    Return,

    // Used only inside Lexer
    OneLineComment,
    OpenSeveralLinesComment,
    CloseSeveralLinesComment,
    Error,
};

class Token {
public:
    Token();
    Token(TokenType type);
    Token(const char* lexeme, TokenType type);
    Token(std::string lexeme, TokenType type);

    const TokenType& type() const { return m_type; }
    const std::string& lexeme() const { return m_lexeme; }

    static std::string typeToString(const Token& tt);

private:
    std::string m_lexeme;
    TokenType m_type;
};
}