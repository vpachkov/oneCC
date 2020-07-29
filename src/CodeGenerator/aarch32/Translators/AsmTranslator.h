#pragma once

#include "AbstractAarch32Translator.h"

namespace oneCC::CodeGenerator::Aarch32 {

class AsmTranslator final : public AbstractAarch32Translator {
public:
    AsmTranslator() = default;

    void ADD_reg(Register& Rd, Register& Rn, Register& Rm) override;
    void ADD_reg_rrx(Register& Rd, Register& Rn, Register& Rm, uint32_t amount) override;
    void ADD_reg_shift_or_rotate(Register& Rd, Register& Rn, Register& Rm, ShiftType stype, uint32_t amount) override;
    void ADD_imm12(Register& Rd, Register& Rn, uint16_t imm12) override;
    void BX(Register& Rm) override;
    void LDR_imm_offset(Register& Rt, Register& Rn, int16_t imm12) override;
    void LDR_imm_pre_indexed(Register& Rt, Register& Rn, int16_t imm12) override;
    void LDR_imm_post_indexed(Register& Rt, Register& Rn, int16_t imm12) override;
    void LDR_reg_offset(Register& Rt, Register& Rn, Register& Rm, int16_t imm12, int16_t shift = 0) override;
    void LDR_reg_pre_indexed(Register& Rt, Register& Rn, Register& Rm, int16_t imm12, int16_t shift = 0) override;
    void LDR_reg_post_indexed(Register& Rt, Register& Rn, Register& Rm, int16_t imm12, int16_t shift = 0) override;
    void MOV_reg(Register& Rd, Register& Rm) override;
    void MOV_reg_rrx(Register& Rd, Register& Rm, uint32_t amount) override;
    void MOV_reg_shift_or_rotate(Register& Rd, Register& Rm, ShiftType stype, uint32_t amount) override;
    void MOV_imm16(Register& Rd, uint16_t imm16) override;
    void MOVT_imm16(Register& Rd, uint16_t imm16) override;
    void MOVV_imm32(Register& Rd, uint32_t imm32) override;
    void POP_multiple_registers(RegisterList list) override;
    void PUSH_multiple_registers(RegisterList list) override;
    void STR_imm_offset(Register& Rt, Register& Rn, int16_t imm12) override;
    void STR_imm_pre_indexed(Register& Rt, Register& Rn, int16_t imm12) override;
    void STR_imm_post_indexed(Register& Rt, Register& Rn, int16_t imm12) override;
    void STR_reg_offset(Register& Rt, Register& Rn, Register& Rm, int16_t imm12, int16_t shift = 0) override;
    void STR_reg_pre_indexed(Register& Rt, Register& Rn, Register& Rm, int16_t imm12, int16_t shift = 0) override;
    void STR_reg_post_indexed(Register& Rt, Register& Rn, Register& Rm, int16_t imm12, int16_t shift = 0) override;
    void SUB_reg(Register& Rd, Register& Rn, Register& Rm) override;
    void SUB_reg_rrx(Register& Rd, Register& Rn, Register& Rm, uint32_t amount) override;
    void SUB_reg_shift_or_rotate(Register& Rd, Register& Rn, Register& Rm, ShiftType stype, uint32_t amount) override;
    void SUB_imm12(Register& Rd, Register& Rn, uint16_t imm12) override;

    void addLabel(const char* text);
};

}