#include "Lexer.h"
#include <iostream>

namespace oneCC::Lexer {

Lexer::Lexer(std::unique_ptr<std::ifstream> fileStream)
    : TextSequencer(std::move(fileStream))
    , m_keywordManager(KeywordManager::makeStandard())
    , m_active_token(-1)
    , m_cache()
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

readNumberIntStartState:
    if (lookupChar() == '0') {
        val += nextChar();
        goto readNumberNotDecFormat;
    }
readNumberIntState:
    if (isNextDigit()) {
        val += nextChar();
        goto readNumberIntState;
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

readNumberNotDecFormat:
    if (lookupChar() == 'b') {
        val += nextChar();
        goto readNumberBinFormat;
    } else if (lookupChar() == 'x') {
        val += nextChar();
        goto readNumberHexFormat;
    } else {
        goto readNumberIntState;
    }

readNumberBinFormat:
    if (lookupChar() == '0') {
        val += nextChar();
        goto readNumberBinFormat;
    } else if (lookupChar() == '1') {
        val += nextChar();
        goto readNumberBinFormat;
    } else if (isNextDigit()) {
        goto readNumberErrorState;
    } else if (isNextAlpha()) {
        goto readNumberErrorState;
    } else {
        return Token(val, TokenType::IntConst);
    }

readNumberHexFormat:
    if (isNextHex()) {
        val += nextChar();
        goto readNumberHexFormat;
    } else if (isNextDigit()) {
        val += nextChar();
        goto readNumberHexFormat;
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

    if (isNextWordCapableSymbol())
        val += nextChar();
    else
        return Token(TokenType::Error);

    while (isNextWordCapableSymbol() || isNextDigit()) {
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

// TODO: add support for UNICODE
char Lexer::asEscapeSequence(char c)
{
    switch (c) {
    case '\'':
        return 0x27;
    case '\"':
        return 0x22;
    case '?':
        return 0x3f;
    case '\\':
        return 0x5c;
    case '0':
        return 0x00;
    case 'a':
        return 0x07;
    case 'b':
        return 0x08;
    case 'f':
        return 0x0c;
    case 'n':
        return 0x0a;
    case 'r':
        return 0x0d;
    case 't':
        return 0x09;
    case 'v':
        return 0x0b;
    default:
        return -1;
    }
}

Token Lexer::readString()
{
    std::string val;

    if (isNextDoubleQuote()) {
        nextChar();
    }

    bool escape_seq = false;
    for (;;) {
        if (escape_seq) {
            if (switchLine()) {
                nextLine();
            } else if (char eseq = asEscapeSequence(lookupChar()); eseq != -1) {
                val += eseq;
                nextChar();
            } else {
                return Token(TokenType::Error);
            }
            escape_seq = false;
        } else {
            if (lookupChar() == EOF) {
                return Token(TokenType::Error);
            } else if (lookupChar() == '\\') {
                escape_seq = true;
                nextChar();
            } else if (isNextDoubleQuote()) {
                nextChar();
                return Token(val, TokenType::ConstString);
            } else {
                val += nextChar();
            }
        }
    }
    return Token(TokenType::Error);
}

Token Lexer::readChar()
{
    if (isNextSingleQuote()) {
        nextChar();
    }
    std::string val;
    if (lookupChar() == '\\') {
        nextChar();
        if (char eseq = asEscapeSequence(lookupChar()); eseq != -1) {
            val += eseq;
            nextChar();
        } else {
            return Token(TokenType::Error);
        }
    } else if (isNextSingleQuote()) {
        nextChar();
        return Token(val, TokenType::ConstChar);
    } else {
        val += nextChar();
    }
    if (isNextSingleQuote()) {
        nextChar();
        return Token(val, TokenType::ConstChar);
    } else {
        return Token(TokenType::Error);
    }
}

bool Lexer::tokinizeFile()
{
    Token res;

    while (!isNextEOF()) {
        skipGaps();
        while (switchLine()) {
            nextLine();
            skipGaps();
        }

        if (isNextDigit()) {
            res = readNumber();
        } else if (isNextWordCapableSymbol()) {
            res = m_keywordManager->process(readWord());
        } else if (isNextDoubleQuote()) {
            res = readString();
        } else if (isNextSingleQuote()) {
            res = readChar();
        } else if (isNextPunct()) {
            res = m_keywordManager->process(readPunct());
        } else if (isNextEOF()) {
            res = Token(TokenType::EndOfFile);
        }

        if (res.type() == TokenType::Error) {
            throw std::runtime_error(errorMsg());
        }

        m_cache.push_back(res);
    }

    return true;
}

Token Lexer::lookupToken(int offset)
{
    int index = m_active_token + offset;
    if (index < 0 || index >= m_cache.size()) [[unlikely]] {
        return Token(TokenType::EndOfFile);
    }
    return m_cache[index];
}

Token Lexer::lookupToken()
{
    return lookupToken(1);
}

Token Lexer::skipToken(int offset)
{
    m_active_token += offset + 1;
    return lookupToken(0);
}

Token Lexer::skipToken()
{
    m_active_token++;
    return lookupToken(0);
}

std::string Lexer::errorMsg()
{
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