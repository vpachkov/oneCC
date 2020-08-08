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

    TranslatedOpcode(const std::string& s, const std::string& label)
        : m_asm(s)
        , m_label(label)
        , m_isWithLabel(true)
    {
    }

    TranslatedOpcode(std::string&& s, std::string&& label)
        : m_asm(std::move(s))
        , m_label(std::move(label))
        , m_isWithLabel(true)
    {
    }

    TranslatedOpcode(const TranslatedOpcode& t)
        : m_asm(t.m_asm)
        , m_label(t.m_label)
        , m_isWithLabel(t.m_isWithLabel)
    {
    }

    TranslatedOpcode& operator=(const TranslatedOpcode& other)
    {
        m_asm = other.m_asm;
        m_label = other.m_label;
        m_isWithLabel = other.m_isWithLabel;
        return *this;
    }

    TranslatedOpcode(TranslatedOpcode&& t)
        : m_asm(std::move(t.m_asm))
        , m_label(std::move(t.m_label))
        , m_isWithLabel(t.m_isWithLabel)
    {
    }

    TranslatedOpcode& operator=(TranslatedOpcode&& other)
    {
        m_asm = std::move(other.m_asm);
        m_label = std::move(other.m_label);
        m_isWithLabel = other.m_isWithLabel;
        return *this;
    }

    void setLabel(const std::string& label)
    {
        if (m_isWithLabel) {
            m_label = label;
        }
    }

    void print()
    {
        std::cout << m_asm;
        if (!m_label.empty()) {
            std::cout << " " << m_label;
        }
        std::cout << "\n";
    }

private:
    std::string m_asm;
    std::string m_label;
    bool m_isWithLabel { false };
};

}