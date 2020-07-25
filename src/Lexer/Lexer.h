#pragma once

#include "KeywordManager.h"
#include "TextSequencer.h"
#include "Token.h"
#include <memory>
#include <stdexcept>
#include <vector>

namespace oneCC::Lexer {
class Lexer : TextSequencer {
public:
    Lexer(const char* filename);
    Lexer(std::unique_ptr<std::ifstream>&& fileStream);
    bool tokinizeFile();
    Token lookupToken(int offset);
    Token lookupToken();
    Token skipToken(int offset);
    Token skipToken();

    int lineIndex() { return lineSwitched(); }
    int lineOffset() { return currentOffset(); }

    bool isComment() { return m_oneLineComment || m_multiLineComment; }
    void setOneLineComment(bool val) { m_oneLineComment = val; }
    void setMultilineComment(bool val) { m_multiLineComment = val; }

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

    bool m_oneLineComment { false };
    bool m_multiLineComment { false };
};
}
