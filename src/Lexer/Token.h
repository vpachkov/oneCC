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
    
    // Boolean
    // Add boolean types ONLY HERE!
    _BooleanStart,
    Less,
    Bigger,
    Equal,
    _BooleanEnd,

    // Others
    EndOfFile,

    // Types
    IntConst,
    FloatConst,
    StringConst,

    TypeInt,
    TypeFloat,
    TypeBoolean,

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

static const char* tokenTypeToString(TokenType token) {
    static const char* tokens[] = {
            "Identifier",
            "Punct",
            "ConstString",
            "ConstChar",
            "Comma",

            // Keywords
            "if",
            "else",
            "while",

            // Binary Operations
            "+",
            "-",
            "*",
            "/",
            "==",

            ">",

            // Others
            "EndOfFile",

            // Types
            "IntConst",
            "FloatConst",
            "StringConst",

            "int",
            "float",
            "bool",

            // Brackets
            "(",
            ")",
            "[",
            "]",
            "{",
            "}",

            "=",

            ";",

            "return",

            // Used only inside Lexer
            "//",
            "/*",
            "*/",
            "error",
    };

    return tokens[token];
}

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