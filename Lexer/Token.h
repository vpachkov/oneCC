#pragma once
#include <string>

namespace oneCC::Lexer {
    enum TokenType {
        Number,
        Word,
        Punct,
        
        // Keywords
        If,
        
        // Operations
        Bigger,

        // Others
        EndOfFile,
    };

    class Token {
    public:
        Token(const char* value, TokenType type);
        Token(std::string value, TokenType type);

        TokenType type() { return m_type; }
        std::string value() { return m_value; }
    private:
        std::string m_value;
        TokenType m_type;
    };
}