#include "TextSequencer.h"
#include <iostream>

namespace oneCC::Lexer {
TextSequencer::TextSequencer(std::shared_ptr<std::ifstream> fileStream)
    : m_fileStream(fileStream)
{
    assert(m_fileStream->is_open());
}

// Returns next char and doesn't seek the file.
char TextSequencer::lookupChar()
{
    char res = nextChar();
    if (isValidChar(res))
        m_fileStream->seekg(-1, m_fileStream->cur);
    return res;
}

// Returns next char and seek the file.
char TextSequencer::nextChar()
{
    assert(m_fileStream->is_open());

    char res;
    if (m_fileStream->get(res)) {
        return res;
    }

    return EOF;
}

TextSequencer::~TextSequencer()
{
}
}