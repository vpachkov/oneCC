#pragma once

#include "../Common/ModRM.h"
#include "../Common/Regs.h"
#include <cstdint>

namespace oneCC::CodeGenerator::X86_32 {

class AbstractX86_32Translator {
public:
    AbstractX86_32Translator() = default;

    // Generated (test part)
    virtual void ADC_rm32_reg32(RM op1, Register op2) {}
    virtual void ADC_rm8_reg8(RM op1, Register op2) {}
    virtual void ADD_AL_imm8(uint8_t op2) {}
    virtual void ADD_EAX_imm32(uint32_t op2) {}
    virtual void ADD_reg32_rm32(Register op1, RM op2) {}
    virtual void ADD_reg8_rm8(Register op1, RM op2) {}
    virtual void ADD_rm32_reg32(RM op1, Register op2) {}
    virtual void ADD_rm8_reg8(RM op1, Register op2) {}
    virtual void OR_AL_imm8(uint8_t op2) {}
    virtual void OR_EAX_imm32(uint32_t op2) {}
    virtual void OR_reg32_rm32(Register op1, RM op2) {}
    virtual void OR_reg8_rm8(Register op1, RM op2) {}
    virtual void OR_rm32_reg32(RM op1, Register op2) {}
    virtual void OR_rm8_reg8(RM op1, Register op2) {}
    virtual void POP_ES() {}
    virtual void PUSH_CS() {}
    virtual void PUSH_ES() {}
};

}