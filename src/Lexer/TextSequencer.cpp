#include "TextSequencer.h"
#include <cassert>
#include <iostream>
#include <utility>

namespace oneCC::Lexer {

TextSequencer::TextSequencer(const char* filename)
    : m_fileStream(std::make_unique<std::ifstream>(filename))
    , m_currentLine("")
    , m_switchLine(true)
    , m_fileEnded(false)
    , m_passed(0)
    , m_linesSwitched(0)
{
    assert(m_fileStream->is_open());
}

TextSequencer::TextSequencer(std::unique_ptr<std::ifstream>&& fileStream)
    : m_fileStream(std::move(fileStream))
    , m_currentLine("")
    , m_switchLine(true)
    , m_fileEnded(false)
    , m_passed(0)
    , m_linesSwitched(0)
{
    assert(m_fileStream->is_open());
}

void TextSequencer::nextLine()
{
    assert(m_fileStream->is_open());
    while (m_switchLine) {
        if (std::getline(*m_fileStream, m_currentLine)) {
            m_passed = 0;
            m_switchLine = m_currentLine.empty();
        } else {
            m_fileEnded = true;
            m_switchLine = false;
            m_currentLine = "";
        }
    }
    m_linesSwitched++;
}

// Returns next char at position @offset and doesn't seek the file.
char TextSequencer::lookupChar(int offset)
{
    if (m_passed + offset - 1 < m_currentLine.size()) {
        return m_currentLine[m_passed + offset - 1];
    }
    return m_fileEnded ? EOF : '\n';
}

// Returns next char and doesn't seek the file.
char TextSequencer::lookupChar()
{
    return lookupChar(1);
}

// Returns next char and seek the file.
char TextSequencer::nextChar()
{
    m_passed++;
    if (m_passed == m_currentLine.size()) {
        m_switchLine = true;
    }
    return lookupChar(0);
}

TextSequencer::~TextSequencer() = default;

}