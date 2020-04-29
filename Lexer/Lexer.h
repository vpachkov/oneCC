#pragma once

#include <memory>

#include "Token.h"
#include "TextSequencer.h"

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

    };
}
