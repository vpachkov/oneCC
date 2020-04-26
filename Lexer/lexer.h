#pragma once

#include <memory>

#include "../TextSequencer/text_sequencer.h"

namespace oneCC {
namespace Lexer {
    class Lexer {
    public:
        Lexer(std::shared_ptr<TextSequencer> _textSequencer);
        int test_func();
    private:
        std::shared_ptr<TextSequencer> m_textSequencer;
    };
}
}
