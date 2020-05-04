#include "Lexer.h"

namespace oneCC::Lexer {

Lexer::Lexer(std::shared_ptr<std::ifstream> fileStream)
    : TextSequencer(fileStream)
    , m_keywordManager(KeywordManager::makeStandart())
{
}

void Lexer::skipGaps()
{
    while (isspace(lookupChar())) {
        nextChar();
    }
}

Token Lexer::readNumber()
{
    std::string val;

readNumberIntState:
    if (isNextDigit()) {
        val += nextChar();
        goto readNumberIntState;
    } else if (lookupChar() == '.') {
        val += nextChar();
        goto readNumberFloatState;
    } else if (lookupChar() == 'e') {
        val += nextChar();
        goto readNumberExpStateStart;
    } else {
        return Token(val, TokenType::IntConst);
    }

readNumberFloatState:
    if (isNextDigit()) {
        val += nextChar();
        goto readNumberFloatState;
    } else if (lookupChar() == 'e') {
        val += nextChar();
        goto readNumberExpStateStart;
    } else {
        return Token(val, TokenType::FloatConst);
    }

readNumberExpStateStart:
    if (isNextDigit()) {
        val += nextChar();
        goto readNumberExpState;
    } else if (lookupChar() == '+') {
        val += nextChar();
        goto readNumberExpState;
    } else if (lookupChar() == '-') {
        val += nextChar();
        goto readNumberExpState;
    } else {
        goto readNumberErrorState;
    }

readNumberExpState:
    while (isNextDigit()) {
        val += nextChar();
    }

    return Token(val, TokenType::FloatConst);

readNumberErrorState:
    return Token("", TokenType::EndOfFile);
}

Token Lexer::readWord()
{
    std::string val;
    while (isNextAlpha()) {
        val += nextChar();
    }
    return Token(val, TokenType::Identifier);
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
        return m_keywordManager->process(readWord());
    } else if (isNextPunct()) {
        return m_keywordManager->process(readPunct());
    }
    return Token("", TokenType::EndOfFile);
}

}