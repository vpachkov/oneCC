#include "Lexer.h"

namespace oneCC::Lexer {

Lexer::Lexer(std::shared_ptr<std::ifstream> fileStream)
    : TextSequencer(fileStream)
    , m_keywordManager(KeywordManager::makeStandart())
{
}

void Lexer::skipGaps()
{
    while (isNextSpace()) {
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
    } else if (isNextAlpha()) {
        goto readNumberErrorState;
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
    } else if (isNextAlpha()) {
        goto readNumberErrorState;
    } else {
        return Token(val, TokenType::FloatConst);
    }

readNumberExpStateStart:
    if (isNextDigit()) {
        val += nextChar();
        goto readNumberExpState;
    } else if (lookupChar() == '+' || lookupChar() == '-') {
        val += nextChar();
        goto readNumberExpState;
    } else {
        goto readNumberErrorState;
    }

readNumberExpState:
    while (isNextDigit()) {
        val += nextChar();
    }

    if (isNextAlpha()) {
        goto readNumberErrorState;
    }

    return Token(val, TokenType::FloatConst);

readNumberErrorState:
    return Token(TokenType::Error);
}

Token Lexer::readWord()
{
    std::string val;

    if (isNextAlpha())
        val += nextChar();
    else
        return Token(TokenType::Error);
    
    while (isNextAlpha() || isNextDigit()) {
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
    Token res;
    skipGaps();
    if (switchLine()) {
        nextLine();
        skipGaps();
    }

    if (isNextDigit()) {
        res = readNumber();
    } else if (isNextAlpha()) {
        res = m_keywordManager->process(readWord());
    } else if (isNextPunct()) {
        res = m_keywordManager->process(readPunct());
    } else if (isNextEOF()) {
        res = Token(TokenType::EndOfFile);
    }

    if (res.type() == TokenType::Error) {
        throw std::runtime_error(errorMsg());
    }

    return res;
}

std::string Lexer::errorMsg() {
    std::string msg;
    msg += "Lexer: unexpected symbol\n\u001b[31m";
    msg += currentLine() + "\n";
    for (int i = 0; i < currentLine().size(); i++) {
        if (i == currentOffset()) {
            msg += '^';
        } else {
            msg += '~';
        }
    }
    msg += "\u001b[0m";
    return msg;
}

}