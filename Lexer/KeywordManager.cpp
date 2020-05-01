#include "KeywordManager.h"

namespace oneCC::Lexer {

KeywordManager::KeywordManager()
{
}

void KeywordManager::addKeyword(Token token)
{
    m_storage[token.value()] = token.type();
}

Token KeywordManager::process(Token token)
{
    if (auto el = m_storage.find(token.value()); el != m_storage.end()) {
        return Token(token.value(), el->second);
    }
    return token;
}

std::shared_ptr<KeywordManager> KeywordManager::makeStandart()
{
    auto man = std::make_shared<KeywordManager>();
    man->addKeyword(Token("if", TokenType::If));
    man->addKeyword(Token(">", TokenType::Bigger));
    return man;
}

}