#include "lexer.h"

namespace oneCC {
namespace Lexer {

    Lexer::Lexer(std::shared_ptr<TextSequencer> _textSequencer)
    {
        m_textSequencer = _textSequencer;
    }

}
}