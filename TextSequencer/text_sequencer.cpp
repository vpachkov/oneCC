#include "text_sequencer.h"

namespace oneCC {
namespace Lexer {
    TextSequencer::TextSequencer(std::shared_ptr<std::string> string_ptr)
    {
        assert(string_ptr != nullptr);
        m_fileStream.open(string_ptr->c_str());
    }

    std::string TextSequencer::getNextLine()
    {
        assert(m_fileStream.is_open());
        std::string s;
        std::getline(m_fileStream, s);
        return s;
    }

    TextSequencer::~TextSequencer() {
        if (m_fileStream.is_open()) {
            m_fileStream.close();
        }
    }
}
}