#pragma once

#include <vector>
#include <memory>
#include <stdexcept>
#include "KeywordManager.h"
#include "TextSequencer.h"
#include "Token.h"

namespace oneCC::Lexer {
class Lexer : TextSequencer {
public:
    Lexer(std::shared_ptr<std::ifstream> fileStream);
    bool tokinizeFile();
    Token lookupToken(int offset);
    Token lookupToken();
    Token nextToken();

private:
    void skipGaps();
    Token readNumber();
    Token readWord();
    Token readPunct();
    Token readString();
    Token readChar();
    char asEscapeSequence(char c);
    std::string errorMsg();

    std::shared_ptr<KeywordManager> m_keywordManager;
    std::vector<Token> m_cache;
    int m_active_token;
};
}
