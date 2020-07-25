#pragma once

#include "../AST/AbstractAST.h"
#include "x86_32/CodeGenerator.h"
#include "aarch32/CodeGenerator.h"

namespace oneCC::CodeGenerator {

enum TargetPlatform {
    x86_32,
    aarch32,
    UNKNOWN,
};

class CodeGenerator {
public:
    CodeGenerator()
    {
        m_genX86_32 = X86_32::CodeGeneratorX86_32();
        m_genAarch32 = Aarch32::CodeGeneratorAarch32();
    }

    CodeGenerator(TargetPlatform pltf)
    {
        m_platform = pltf;
        m_genX86_32 = X86_32::CodeGeneratorX86_32();
        m_genAarch32 = Aarch32::CodeGeneratorAarch32();
    }

    int start(AST::Node* program)
    {
        if (!program) {
            return -1;
        }

        if (m_platform == UNKNOWN) {
            return -1;
        }

        if (m_platform == x86_32) {
            return m_genX86_32.processTree(program);
        }

        if (m_platform == aarch32) {
            return m_genAarch32.processTree(program);
        }

        return -1;
    }

private:
    TargetPlatform m_platform { UNKNOWN };
    X86_32::CodeGeneratorX86_32 m_genX86_32;
    Aarch32::CodeGeneratorAarch32 m_genAarch32;
};

}