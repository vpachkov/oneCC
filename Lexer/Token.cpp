#include "Token.h"
#include <string>

namespace oneCC::Lexer {
Token::Token() { }

Token::Token(TokenType type)
    : m_lexeme("")
    , m_type(type)
{
}

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

std::string Token::typeToString(const Token& tt)
{
    switch (tt.type()) {
        case IntConst:      return "IntConst";
        case FloatConst:    return "FloatConst";
        case Identifier:    return "Identifier";
        case Punct:         return "Punct";
        case ConstString:   return "ConstString";
        case ConstChar:     return "ConstChar";
        
        // Keywords
        case If:            return "If";
        case TypeInt:       return "TypeInt";
        
        // Operations
        case Bigger:        return "Bigger";
        case Plus:      return "Plus";
        case Multiply:      return "Multiply";
        case Assign:      return "Assign";
        case EndOfStatement:      return "EOS";

        // Brackets
        case OpenRoundBracket:      return "OpenRoundBracket";
        case CloseRoundBracket:     return  "CloseRoundBracket";
        case OpenCurlyBracket:      return "OpenCurlyBracket";
        case CloseCurlyBracket:      return "CloseCurlyBracket";

        // Punctuation
        case Comma:      return "Comma";

        // Others
        case EndOfFile:     return "EOF";
        case Error:         return "ERR";
        case Return:         return "Return";

        default:            return "[Unknown]";
    }
}
}