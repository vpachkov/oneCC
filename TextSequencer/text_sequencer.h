#pragma once

#include <fstream>
#include <memory>
#include <string>

namespace oneCC {
namespace Lexer {
    class TextSequencer {
    public:
        TextSequencer(std::shared_ptr<std::string> string_ptr);
        ~TextSequencer();
        std::string getNextLine();

    private:
        std::ifstream m_fileStream;
    };
}
}