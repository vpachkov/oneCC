#pragma once

#include <iostream>
#ifdef DEBUG_TRANSLATOR_TRACER
#include <experimental/source_location>
#endif

namespace oneCC::CodeGenerator::Aarch32 {

class TranslatedOpcode {
public:
    TranslatedOpcode() = default;
    
    TranslatedOpcode(const std::string& s)
        : m_asm(s)
    {
    }
    
    TranslatedOpcode(std::string&& s)
        : m_asm(std::move(s))
    {
    }

    void print() {
        std::cout << m_asm << "\n";
    }

private:
    std::string m_asm;
};

}