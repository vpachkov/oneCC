#pragma once

#include "../AST/AbstractAST.h"
#include "x86_32/CodeGenerator.h"

namespace oneCC::CodeGenerator {

enum TargetPlatform {
    x86_32,
    UNKNOWN,
};

class CodeGenerator {
public:
    CodeGenerator()
    {
    }

    CodeGenerator(TargetPlatform pltf)
    {
        m_genX86_32 = new X86_32::CodeGeneratorX86_32();
        m_platform = pltf;
    }

    void start()
    {
    }

private:
    TargetPlatform m_platform { UNKNOWN };
    X86_32::CodeGeneratorX86_32* m_genX86_32;
};

}