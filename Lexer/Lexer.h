#pragma once

#include <memory>

#include "KeywordManager.h"
#include "TextSequencer.h"
#include "Token.h"

namespace oneCC::Lexer {
class Lexer : TextSequencer {
public:
    Lexer(std::shared_ptr<std::ifstream> fileStream);
    void skipGaps();
    Token nextToken();

private:
    Token readNumber();
    Token readWord();
    Token readPunct();
    std::shared_ptr<KeywordManager> m_keywordManager;
};
}
