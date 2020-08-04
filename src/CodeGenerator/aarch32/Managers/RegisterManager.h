#pragma once

#include "../Common/Regs.h"
#include <vector>

namespace oneCC::CodeGenerator::Aarch32 {

class CodeGeneratorAarch32;

class RegisterManager {
public:
    RegisterManager(CodeGeneratorAarch32& codeGen);

    bool canUse(const Register& reg);
    Register& chooseRegister();
    Register& chooseRegister(const RegisterData& data);
    Register& chooseRegisterFromBack();
    int resolveForbiddenRegister(Register& reg);

    int write(Register& reg);
    int replace(Register& reg, const RegisterData& data);
    Register& has(const RegisterData& data);

    void useRegister(Register& reg) { m_calleeSavedUsedRegisters |= (1 << (uint32_t)reg.alias()); }
    void resetUsedRegisters() { m_calleeSavedUsedRegisters = 0; }
    RegisterList usedRegisters();

private:
    uint32_t m_calleeSavedUsedRegisters; // Mask
    CodeGeneratorAarch32& m_codeGenerator;
};

}