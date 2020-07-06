#pragma once

#include <fstream>
#include <memory>
#include <string>

namespace oneCC::Lexer {
class TextSequencer {
protected:
    TextSequencer(std::unique_ptr<std::ifstream> fileStream);
    ~TextSequencer();
    char nextChar();
    char lookupChar(int offset);
    char lookupChar();

    bool isNextDigit() { return isdigit(lookupChar()); }
    bool isNextAlpha() { return isalpha(lookupChar()); }
    bool isNextWordCapableSymbol() { return isNextAlpha() || isNextIdentifierAllowPunct(); }
    bool isNextHex() { return isHex(lookupChar()); }
    bool isNextPunct() { return isPunct(lookupChar()); }
    bool isNextSingleQuote() { return lookupChar() == '\''; }
    bool isNextDoubleQuote() { return lookupChar() == '\"'; }
    bool isNextIdentifierAllowPunct() { return isIdentifierAllowPunct(lookupChar()); }
    bool isNextEOF() { return lookupChar() == EOF; }
    bool isNextSpace() { return lookupChar() == ' '; }
    bool isNextNL() { return lookupChar() == '\n'; }

    void nextLine();
    bool switchLine() { return m_switchLine; }
    std::string currentLine() const { return m_currentLine; }
    int currentOffset() const { return m_passed; }

private:
    bool isHex(char c) { return ('a' <= c && c <= 'f') || ('A' <= c && c <= 'F'); }
    bool isPunct(char c) { return ispunct(c) && !isIdentifierAllowPunct(c); }
    bool isIdentifierAllowPunct(char c) { return c == '_' || c == '$'; }

    std::unique_ptr<std::ifstream> m_fileStream;
    std::string m_currentLine;
    int m_passed;
    bool m_switchLine;
    bool m_fileEnded;
};
}