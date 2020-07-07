#include "KeywordManager.h"

namespace oneCC::Lexer {

KeywordManager::KeywordManager()
{
}

void KeywordManager::addKeyword(Token token)
{
    m_storage[token.lexeme()] = token.type();
}

Token KeywordManager::process(Token token)
{
    if (auto el = m_storage.find(token.lexeme()); el != m_storage.end()) {
        return Token(token.lexeme(), el->second);
    }
    return token;
}

std::shared_ptr<KeywordManager> KeywordManager::makeStandart()
{
    auto man = std::make_shared<KeywordManager>();
    man->addKeyword(Token("+", TokenType::Plus));
    man->addKeyword(Token("*", TokenType::Multiply));
    man->addKeyword(Token("/", TokenType::Divide));
    man->addKeyword(Token("(", TokenType::OpenRoundBracket));
    man->addKeyword(Token(")", TokenType::CloseRoundBracket));

    // Types
    man->addKeyword(Token("int", TokenType::TypeInt));
    return man;
}

}