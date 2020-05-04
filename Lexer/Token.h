#pragma once
#include <string>

namespace oneCC::Lexer {
    enum TokenType {
        IntConst,
        FloatConst,
        Identifier,
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
        Token(const char* lexeme, TokenType type);
        Token(std::string lexeme, TokenType type);

        TokenType type() { return m_type; }
        std::string lexeme() { return m_lexeme; }
    private:
        std::string m_lexeme;
        TokenType m_type;
    };
}