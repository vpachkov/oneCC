#pragma once

#include <fstream>
#include <memory>
#include <string>

namespace oneCC::Lexer {
class TextSequencer {
public:
    TextSequencer(std::shared_ptr<std::ifstream> fileStream);
    ~TextSequencer();
    char nextChar();
    char lookupChar();

    bool isNextDigit() { return isdigit(lookupChar()); }
    bool isNextAlpha() { return isalpha(lookupChar()); }
    bool isNextPunct() { return ispunct(lookupChar()); }

private:
    std::shared_ptr<std::ifstream> m_fileStream;
};
}