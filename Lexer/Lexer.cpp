#include "Lexer.h"

namespace oneCC::Lexer {

Lexer::Lexer(std::shared_ptr<std::ifstream> fileStream)
    : TextSequencer(fileStream)
{
}

void Lexer::skipGaps()
{
    while (isspace(lookupChar())) {
        nextChar();
    }
}

// FIXME: currently supports only int
Token Lexer::readNumber()
{
    std::string val;
    while (isNextDigit()) {
        val += nextChar();
    }
    return Token(val, TokenType::Number);
}

Token Lexer::readWord()
{
    std::string val;
    while (isNextAlpha()) {
        val += nextChar();
    }
    return Token(val, TokenType::Word);
}

Token Lexer::readPunct()
{
    std::string val;
    if (isNextPunct()) {
        val += nextChar();
    }
    return Token(val, TokenType::Punct);
}

Token Lexer::nextToken()
{
    skipGaps();
    if (isNextDigit()) {
        return readNumber();
    } else if (isNextAlpha()) {
        return readWord();
    } else if (isNextPunct()) {
        return readPunct();
    }
    return Token("", TokenType::EndOfFile);
}

}