#pragma once

#include "../Common/Regs.h"
#include "../Common/TypesAarch32.h"
#include "TranslatedOpcode.h"
#include <string>

namespace oneCC::CodeGenerator::Aarch32 {

class AbstractAarch32Translator {
public:
    AbstractAarch32Translator() = default;

    // TODO: Add <q> and <c> from dev arm page.
    virtual TranslatedOpcode ADD_reg(Register& Rd, Register& Rn, Register& Rm) { return TranslatedOpcode(); }
    virtual TranslatedOpcode ADD_reg_rrx(Register& Rd, Register& Rn, Register& Rm, uint32_t amount) { return TranslatedOpcode(); }
    virtual TranslatedOpcode ADD_reg_shift_or_rotate(Register& Rd, Register& Rn, Register& Rm, ShiftType stype, uint32_t amount) { return TranslatedOpcode(); }
    virtual TranslatedOpcode ADD_imm12(Register& Rd, Register& Rn, uint16_t imm12) { return TranslatedOpcode(); }
    virtual TranslatedOpcode BL(uint32_t imm24, const std::string& label) { return TranslatedOpcode(); }
    virtual TranslatedOpcode BLX(uint32_t imm24, const std::string& label) { return TranslatedOpcode(); }
    virtual TranslatedOpcode BX(Register& Rm) { return TranslatedOpcode(); }
    virtual TranslatedOpcode LDR_imm_offset(Register& Rt, Register& Rn, int16_t imm12) { return TranslatedOpcode(); }
    virtual TranslatedOpcode LDR_imm_pre_indexed(Register& Rt, Register& Rn, int16_t imm12) { return TranslatedOpcode(); }
    virtual TranslatedOpcode LDR_imm_post_indexed(Register& Rt, Register& Rn, int16_t imm12) { return TranslatedOpcode(); }
    virtual TranslatedOpcode LDR_reg_offset(Register& Rt, Register& Rn, Register& Rm, int16_t imm12, int16_t shift = 0) { return TranslatedOpcode(); }
    virtual TranslatedOpcode LDR_reg_pre_indexed(Register& Rt, Register& Rn, Register& Rm, int16_t imm12, int16_t shift = 0) { return TranslatedOpcode(); }
    virtual TranslatedOpcode LDR_reg_post_indexed(Register& Rt, Register& Rn, Register& Rm, int16_t imm12, int16_t shift = 0) { return TranslatedOpcode(); }
    // virtual TranslatedOpcode MOV(Register& Rd, ModifiedConst) { return TranslatedOpcode(); }
    virtual TranslatedOpcode MOV_reg(Register& Rd, Register& Rm) { return TranslatedOpcode(); }
    virtual TranslatedOpcode MOV_reg_rrx(Register& Rd, Register& Rm, uint32_t amount) { return TranslatedOpcode(); }
    virtual TranslatedOpcode MOV_reg_shift_or_rotate(Register& Rd, Register& Rm, ShiftType stype, uint32_t amount) { return TranslatedOpcode(); }
    virtual TranslatedOpcode MOV_imm16(Register& Rd, uint16_t imm16) { return TranslatedOpcode(); }
    virtual TranslatedOpcode MOVT_imm16(Register& Rd, uint16_t imm16) { return TranslatedOpcode(); }
    virtual TranslatedOpcode MOVV_imm32(Register& Rd, uint32_t imm32) { return TranslatedOpcode(); } // virtual
    virtual TranslatedOpcode POP_multiple_registers(RegisterList list) { return TranslatedOpcode(); }
    virtual TranslatedOpcode PUSH_multiple_registers(RegisterList list) { return TranslatedOpcode(); }
    virtual TranslatedOpcode STR_imm_offset(Register& Rt, Register& Rn, int16_t imm12) { return TranslatedOpcode(); }
    virtual TranslatedOpcode STR_imm_pre_indexed(Register& Rt, Register& Rn, int16_t imm12) { return TranslatedOpcode(); }
    virtual TranslatedOpcode STR_imm_post_indexed(Register& Rt, Register& Rn, int16_t imm12) { return TranslatedOpcode(); }
    virtual TranslatedOpcode STR_reg_offset(Register& Rt, Register& Rn, Register& Rm, int16_t imm12, int16_t shift = 0) { return TranslatedOpcode(); }
    virtual TranslatedOpcode STR_reg_pre_indexed(Register& Rt, Register& Rn, Register& Rm, int16_t imm12, int16_t shift = 0) { return TranslatedOpcode(); }
    virtual TranslatedOpcode STR_reg_post_indexed(Register& Rt, Register& Rn, Register& Rm, int16_t imm12, int16_t shift = 0) { return TranslatedOpcode(); }
    virtual TranslatedOpcode SUB_reg(Register& Rd, Register& Rn, Register& Rm) { return TranslatedOpcode(); }
    virtual TranslatedOpcode SUB_reg_rrx(Register& Rd, Register& Rn, Register& Rm, uint32_t amount) { return TranslatedOpcode(); }
    virtual TranslatedOpcode SUB_reg_shift_or_rotate(Register& Rd, Register& Rn, Register& Rm, ShiftType stype, uint32_t amount) { return TranslatedOpcode(); }
    virtual TranslatedOpcode SUB_imm12(Register& Rd, Register& Rn, uint16_t imm12) { return TranslatedOpcode(); }
};

}