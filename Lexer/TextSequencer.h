#pragma once

#include <fstream>
#include <memory>
#include <string>

namespace oneCC::Lexer {
class TextSequencer {
protected:
    TextSequencer(std::shared_ptr<std::ifstream> fileStream);
    ~TextSequencer();
    char nextChar();
    char lookupChar(int offset);
    char lookupChar();

    bool isNextDigit() { return isdigit(lookupChar()); }
    bool isNextAlpha() { return isalpha(lookupChar()); }
    bool isNextHex() { return isHex(lookupChar()); }
    bool isNextPunct() { return ispunct(lookupChar()); }
    bool isNextEOF() { return lookupChar() == EOF; }
    bool isNextSpace() { return lookupChar() == ' '; }
    bool isNextNL() { return lookupChar() == '\n'; }

    void nextLine();
    bool switchLine() { return m_switchLine; }
    std::string currentLine() const { return m_currentLine; }
    int currentOffset() const { return m_passed; }

private:
    bool isHex(char c) { return ('a' <= c && c <= 'f') || ('A' <= c && c <= 'F'); }

    std::shared_ptr<std::ifstream> m_fileStream;
    std::string m_currentLine;
    int m_passed;
    bool m_switchLine;
    bool m_fileEnded;
};
}