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
    auto man = std::make_shared<KeywordManager>();
    man->addKeyword(Token("+", TokenType::Plus));
    man->addKeyword(Token("-", TokenType::Minus));
    man->addKeyword(Token("*", TokenType::Multiply));
    man->addKeyword(Token("/", TokenType::Divide));
    man->addKeyword(Token("=", TokenType::Assign));

    // Boolean
    man->addKeyword(Token("==", TokenType::Equal));
    man->addKeyword(Token(">", TokenType::Bigger));
    man->addKeyword(Token("<", TokenType::Less));

    // Types
    man->addKeyword(Token("int", TokenType::TypeInt));

    // Punctuation
    man->addKeyword(Token(";", TokenType::EndOfStatement));
    man->addKeyword(Token(",", TokenType::Comma));
    man->addKeyword(Token("(", TokenType::OpenRoundBracket));
    man->addKeyword(Token(")", TokenType::CloseRoundBracket));
    man->addKeyword(Token("{", TokenType::OpenCurlyBracket));
    man->addKeyword(Token("}", TokenType::CloseCurlyBracket));

    // Keywords
    man->addKeyword(Token("return", TokenType::Return));
    man->addKeyword(Token("if", TokenType::If));
    man->addKeyword(Token("while", TokenType::While));
    man->addKeyword(Token("else", TokenType::Else));

    // Comments, used only inside Lexer
    man->addKeyword(Token("//", TokenType::OneLineComment));
    man->addKeyword(Token("/*", TokenType::OpenSeveralLinesComment));
    man->addKeyword(Token("*/", TokenType::CloseSeveralLinesComment));

    return man;
}

}