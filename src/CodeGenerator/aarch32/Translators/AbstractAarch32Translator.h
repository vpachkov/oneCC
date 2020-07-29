#pragma once

#include "../Common/Regs.h"
#include "../Common/TypesAarch32.h"

namespace oneCC::CodeGenerator::Aarch32 {

class AbstractAarch32Translator {
public:
    AbstractAarch32Translator() = default;

    // TODO: Add <q> and <c> from dev arm page.
    virtual void ADD_reg(Register& Rd, Register& Rn, Register& Rm) {}
    virtual void ADD_reg_rrx(Register& Rd, Register& Rn, Register& Rm, uint32_t amount) {}
    virtual void ADD_reg_shift_or_rotate(Register& Rd, Register& Rn, Register& Rm, ShiftType stype, uint32_t amount) {}
    virtual void ADD_imm12(Register& Rd, Register& Rn, uint16_t imm12) {}
    virtual void BX(Register& Rm) {}
    virtual void LDR_imm_offset(Register& Rt, Register& Rn, int16_t imm12) {}
    virtual void LDR_imm_pre_indexed(Register& Rt, Register& Rn, int16_t imm12) {}
    virtual void LDR_imm_post_indexed(Register& Rt, Register& Rn, int16_t imm12) {}
    virtual void LDR_reg_offset(Register& Rt, Register& Rn, Register& Rm, int16_t imm12, int16_t shift = 0) {}
    virtual void LDR_reg_pre_indexed(Register& Rt, Register& Rn, Register& Rm, int16_t imm12, int16_t shift = 0) {}
    virtual void LDR_reg_post_indexed(Register& Rt, Register& Rn, Register& Rm, int16_t imm12, int16_t shift = 0) {}
    // virtual void MOV(Register& Rd, ModifiedConst) {}
    virtual void MOV_reg(Register& Rd, Register& Rm) {}
    virtual void MOV_reg_rrx(Register& Rd, Register& Rm, uint32_t amount) {}
    virtual void MOV_reg_shift_or_rotate(Register& Rd, Register& Rm, ShiftType stype, uint32_t amount) {}
    virtual void MOV_imm16(Register& Rd, uint16_t imm16) {}
    virtual void MOVT_imm16(Register& Rd, uint16_t imm16) {}
    virtual void MOVV_imm32(Register& Rd, uint32_t imm32) {} // virtual
    virtual void POP_multiple_registers(RegisterList list) {}
    virtual void PUSH_multiple_registers(RegisterList list) {}
    virtual void STR_imm_offset(Register& Rt, Register& Rn, int16_t imm12) {}
    virtual void STR_imm_pre_indexed(Register& Rt, Register& Rn, int16_t imm12) {}
    virtual void STR_imm_post_indexed(Register& Rt, Register& Rn, int16_t imm12) {}
    virtual void STR_reg_offset(Register& Rt, Register& Rn, Register& Rm, int16_t imm12, int16_t shift = 0) {}
    virtual void STR_reg_pre_indexed(Register& Rt, Register& Rn, Register& Rm, int16_t imm12, int16_t shift = 0) {}
    virtual void STR_reg_post_indexed(Register& Rt, Register& Rn, Register& Rm, int16_t imm12, int16_t shift = 0) {}
    virtual void SUB_reg(Register& Rd, Register& Rn, Register& Rm) {}
    virtual void SUB_reg_rrx(Register& Rd, Register& Rn, Register& Rm, uint32_t amount) {}
    virtual void SUB_reg_shift_or_rotate(Register& Rd, Register& Rn, Register& Rm, ShiftType stype, uint32_t amount) {}
    virtual void SUB_imm12(Register& Rd, Register& Rn, uint16_t imm12) {}
};

}