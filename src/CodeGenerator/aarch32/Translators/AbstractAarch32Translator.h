#pragma once

// #include "../Common/Regs.h"
#include "../Common/TypesAarch32.h"

namespace oneCC::CodeGenerator::Aarch32 {

class AbstractAarch32Translator {
public:
    AbstractAarch32Translator() = default;

    // TODO: Add <q> and <c> from dev arm page.
    virtual void ADD_imm12(Register& Rd, Register& Rn, uint16_t imm12) {}
    virtual void BX(Register& Rm) {}
    virtual void POP_multiple_registers(RegisterList list) {}
    virtual void PUSH_multiple_registers(RegisterList list) {}
    virtual void SUB_imm12(Register& Rd, Register& Rn, uint16_t imm12) {}
};

}