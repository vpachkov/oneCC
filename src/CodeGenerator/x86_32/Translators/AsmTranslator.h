#pragma once

#include "../Common/Regs.h"
#include "../Common/ModRM.h"
#include <cstdint>

namespace oneCC::CodeGenerator::X86_32 {

class AsmTranslator final {
public:
    AsmTranslator() = default;

    // Generated (test part)
    void ADD_rm8_reg8(RM op1, Register op2);
    void ADD_rm32_reg32(RM op1, Register op2);
    void ADD_reg8_rm8(Register op1, RM op2);
    void ADD_reg32_rm32(Register op1, RM op2);
    void ADD_AL_imm8(uint8_t op2);
    void ADD_EAX_imm32(uint32_t op2);
    void PUSH_ES();
    void POP_ES();
    void OR_rm8_reg8(RM op1, Register op2);
    void OR_rm32_reg32(RM op1, Register op2);

};

}