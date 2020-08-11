#pragma once

#include "../Common/Regs.h"
#include <vector>

#define FORCE_NOT_USE_OF_REG true

namespace oneCC::CodeGenerator::Aarch32 {

class CodeGeneratorAarch32;

struct FlushEntry {
    int outputLabel;
    uint32_t mask;
    uint32_t origMask;
};

class RegisterManager {
public:
    RegisterManager(CodeGeneratorAarch32& codeGen);

    bool canUse(const Register& reg);
    Register& chooseRegister();
    Register& chooseRegister(const RegisterData& data);
    Register& chooseRegisterFromBack();
    int resolveForbiddenRegister(Register& reg);

    int write(Register& reg);
    int replace(Register& reg, const RegisterData& data, bool forceNotUseOfReg = false);
    Register& has(const RegisterData& data);

    
    // In code area where we don't know where we come from (e.g while, for, goto)
    // we should think that we don't know what we have in registers, just because
    // we don't know from where we have come. For that we regeter flush, and
    // during the whole period of code generation we can change such registers to
    // be flushed.
    int newRegisterFlush();
    int addUnchangedRegistersToFlush(int id, RegisterList reglist);

private:
    uint32_t m_calleeSavedUsedRegisters; // Mask
    CodeGeneratorAarch32& m_codeGenerator;
    std::vector<FlushEntry>m_flushData; // Store all flushes and for each flush it stores a mask.
};

}