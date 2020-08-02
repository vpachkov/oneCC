#pragma once

#include <iostream>
#ifdef DEBUG_TRANSLATOR_TRACER
#include <experimental/source_location>
#endif

namespace oneCC::CodeGenerator::Aarch32 {

class TranslatedOpcode {
public:
    TranslatedOpcode() {}

    TranslatedOpcode(const std::string& s)
        : m_asm(s)
    {
    }

    TranslatedOpcode(std::string&& s)
        : m_asm(std::move(s))
    {
    }

    TranslatedOpcode(const TranslatedOpcode& t)
        : m_asm(t.m_asm)
    {
    }

    TranslatedOpcode& operator=(const TranslatedOpcode& other)
    {
        m_asm = other.m_asm;
        return *this;
    }

    TranslatedOpcode(TranslatedOpcode&& t)
        : m_asm(std::move(t.m_asm))
    {
    }

    TranslatedOpcode& operator=(TranslatedOpcode&& other)
    {
        m_asm = std::move(other.m_asm);
        return *this;
    }

    void print()
    {
        std::cout << m_asm << "\n";
    }

private:
    std::string m_asm;
};

}