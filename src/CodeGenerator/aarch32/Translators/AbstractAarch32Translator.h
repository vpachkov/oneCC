#pragma once

#include "../Common/Regs.h"

namespace oneCC::CodeGenerator::Aarch32 {

class AbstractAarch32Translator {
public:
    AbstractAarch32Translator() = default;

    // TODO: Add <q> and <c> from dev arm page.
    virtual void ADD_imm12(Register& Rd, Register& Rn, uint16_t imm12) {}
    virtual void BX(Register& Rm) {}
    // virtual void MOV(Register& Rd, ModifiedConst) {}
    virtual void MOV_imm16(Register& Rd, uint16_t imm16) {}
    virtual void MOVT_imm16(Register& Rd, uint16_t imm16) {}
    virtual void MOVV_imm32(Register& Rd, uint32_t imm32) {} // virtual
    virtual void POP_multiple_registers(RegisterList list) {}
    virtual void PUSH_multiple_registers(RegisterList list) {}
    virtual void SUB_imm12(Register& Rd, Register& Rn, uint16_t imm12) {}
};

}