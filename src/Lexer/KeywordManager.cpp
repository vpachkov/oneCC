#include "KeywordManager.h"

namespace oneCC::Lexer {

KeywordManager::KeywordManager()
{
}

void KeywordManager::addKeyword(Token token)
{
    m_storage[token.lexeme()] = token.type();
}

KeywordManagerDecision KeywordManager::shouldContinue(const std::string& str)
{
    for (auto kw : m_storage) {
        if (kw.first.size() >= str.size()) {
            if (str.compare(0, str.size(), kw.first) == 0)
                return kw.first.size() == str.size() ? Match : PossibleMatch;
        }
    }
    return NotFound;
}

Token KeywordManager::process(Token token)
{
    if (auto el = m_storage.find(token.lexeme()); el != m_storage.end()) {
        return Token(token.lexeme(), el->second);
    }
    return token;
}

std::shared_ptr<KeywordManager> KeywordManager::makeStandard()
{
    TokenType keywordTokenTypes[] = {
        TokenType::Plus,
        TokenType::Multiply,
        TokenType::Divide,
        TokenType::Assign,

        TokenType::Equal,
        TokenType::Bigger,
        TokenType::Less,
        TokenType::And,
        TokenType::Or,

        TokenType::TypeInt,

        TokenType::EndOfStatement,
        TokenType::Comma,
        TokenType::OpenRoundBracket,
        TokenType::CloseRoundBracket,
        TokenType::OpenCurlyBracket,
        TokenType::CloseCurlyBracket,

        TokenType::Return,
        TokenType::If,
        TokenType::While,
        TokenType::Else,

        TokenType::OneLineComment,
        TokenType::OpenSeveralLinesComment,
        TokenType::CloseSeveralLinesComment,
    };

    auto man = std::make_shared<KeywordManager>();

    for (auto tokenType : keywordTokenTypes) {
        man->addKeyword(Token(tokenTypeToString(tokenType), tokenType));
    }

    return man;
}

}