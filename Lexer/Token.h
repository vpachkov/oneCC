#pragma once
#include <string>

namespace oneCC::Lexer {
    enum TokenType {
        Number,
        Word,
        Punct,
        EndOfFile,
    };

    class Token {
    public:
        Token(std::string value, TokenType type);

        TokenType type() { return m_type; }
        std::string value() { return m_value; }

    private:
        std::string m_value;
        TokenType m_type;
    };
}