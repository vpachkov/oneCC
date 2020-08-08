#pragma once

#include "../Translators/TranslatedOpcode.h"
#include <vector>

#ifdef DEBUG_TRANSLATOR_TRACER
#include <experimental/source_location>
#endif

namespace oneCC::CodeGenerator::Aarch32 {

class CodeGeneratorAarch32;

class OutputNode {
public:
    OutputNode(int id, bool isLabel);
    OutputNode(int id, const TranslatedOpcode& t);
    OutputNode(int id, TranslatedOpcode&& t);

    int id() { return m_id; }
    
    template <typename Callback>
    void foreachChild(Callback callback)
    {
        for (int i : m_children) {
            callback(i);
        }
    }
    void addChild(int id) { m_children.push_back(id); }
    void setOpcode(const TranslatedOpcode& opcode);
    void setOpcode(TranslatedOpcode&& opcode);
    void setVisible(bool val) { m_visible = val; }
    TranslatedOpcode& opcode() { return m_translatedOpcode; }

    bool isLabel() { return m_isLabel; }
    void print();
    
#ifdef DEBUG_TRANSLATOR_TRACER
    void setLocation(const std::experimental::source_location& location) { m_location = location; }
    void setOpcode(const std::experimental::source_location& location, const TranslatedOpcode& t);
    void setOpcode(const std::experimental::source_location& location, TranslatedOpcode&& t);
#endif
private:
    int m_id { 0 };
    bool m_visible { true };
    bool m_isLabel { false };
    TranslatedOpcode m_translatedOpcode;
    std::vector<int> m_children;
#ifdef DEBUG_TRANSLATOR_TRACER
    std::experimental::source_location m_location;
#endif
};

}