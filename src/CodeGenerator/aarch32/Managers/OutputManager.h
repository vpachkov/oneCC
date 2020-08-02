#pragma once

#include "../Common/Regs.h"
#include "../Translators/TranslatedOpcode.h"
#include <vector>

#ifdef DEBUG_TRANSLATOR_TRACER
#include <experimental/source_location>
#endif

namespace oneCC::CodeGenerator::Aarch32 {

class CodeGeneratorAarch32;

class OutputManager {
public:
    OutputManager(CodeGeneratorAarch32& codeGen)
        : m_codeGenerator(codeGen)
    {
    }

    void add(const TranslatedOpcode& t)
    {
        m_translatedOpcodes.push_back(t);
#ifdef DEBUG_TRANSLATOR_TRACER
        m_opcodesLocation.push_back(std::experimental::source_location());
#endif 
    }

#ifdef DEBUG_TRANSLATOR_TRACER
    void add(const std::experimental::source_location& location, const TranslatedOpcode& t)
    {
        m_opcodesLocation.push_back(location);
        m_translatedOpcodes.push_back(t);
    }
#endif

    void print()
    {
        for (int idx = 0; idx < m_translatedOpcodes.size(); idx++) {
#ifdef DEBUG_TRANSLATOR_TRACER
            std::cout << m_opcodesLocation[idx].function_name() << ": " << m_opcodesLocation[idx].line() << " >> ";
#endif
            m_translatedOpcodes[idx].print();
        }
    }

private:
    CodeGeneratorAarch32& m_codeGenerator;
    std::vector<TranslatedOpcode> m_translatedOpcodes;
#ifdef DEBUG_TRANSLATOR_TRACER
    std::vector<std::experimental::source_location> m_opcodesLocation;
#endif
};

}