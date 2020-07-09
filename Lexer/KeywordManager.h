#pragma once

#include "Token.h"
#include <memory>
#include <unordered_map>

namespace oneCC::Lexer {
class KeywordManager {
public:
    KeywordManager();
    Token process(Token token);
    void addKeyword(Token token);
    static std::shared_ptr<KeywordManager> makeStandard();

private:
    std::unordered_map<std::string, TokenType> m_storage;
};

}
