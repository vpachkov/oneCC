#pragma once

#include "Token.h"
#include <memory>
#include <unordered_map>

namespace oneCC::Lexer {

enum KeywordManagerDecision {
    NotFound,
    PossibleMatch,
    Match,
};

class KeywordManager {
public:
    KeywordManager();
    Token process(Token token);
    KeywordManagerDecision shouldContinue(const std::string& str);
    void addKeyword(Token token);
    static std::shared_ptr<KeywordManager> makeStandard();

private:
    std::unordered_map<std::string, TokenType> m_storage;
};

}
