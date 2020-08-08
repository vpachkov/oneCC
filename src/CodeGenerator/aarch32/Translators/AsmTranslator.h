#pragma once

#include "AbstractAarch32Translator.h"

namespace oneCC::CodeGenerator::Aarch32 {

class AsmTranslator final : public AbstractAarch32Translator {
public:
    AsmTranslator() = default;

    TranslatedOpcode ADD_reg(Register& Rd, Register& Rn, Register& Rm) override;
    TranslatedOpcode ADD_reg_rrx(Register& Rd, Register& Rn, Register& Rm, uint32_t amount) override;
    TranslatedOpcode ADD_reg_shift_or_rotate(Register& Rd, Register& Rn, Register& Rm, ShiftType stype, uint32_t amount) override;
    TranslatedOpcode ADD_imm12(Register& Rd, Register& Rn, uint16_t imm12) override;
    TranslatedOpcode BL(uint32_t imm24, const std::string& label) override;
    TranslatedOpcode BLX(uint32_t imm24, const std::string& label) override;
    TranslatedOpcode BX(Register& Rm) override;
    TranslatedOpcode BEQ(uint32_t imm24, const std::string& label) override;
    TranslatedOpcode BNE(uint32_t imm24, const std::string& label) override;
    TranslatedOpcode CMP(Register& Rn, Register& Rm) override;
    TranslatedOpcode LDR_imm_offset(Register& Rt, Register& Rn, int16_t imm12) override;
    TranslatedOpcode LDR_imm_pre_indexed(Register& Rt, Register& Rn, int16_t imm12) override;
    TranslatedOpcode LDR_imm_post_indexed(Register& Rt, Register& Rn, int16_t imm12) override;
    TranslatedOpcode LDR_reg_offset(Register& Rt, Register& Rn, Register& Rm, int16_t imm12, int16_t shift = 0) override;
    TranslatedOpcode LDR_reg_pre_indexed(Register& Rt, Register& Rn, Register& Rm, int16_t imm12, int16_t shift = 0) override;
    TranslatedOpcode LDR_reg_post_indexed(Register& Rt, Register& Rn, Register& Rm, int16_t imm12, int16_t shift = 0) override;
    TranslatedOpcode MOV_reg(Register& Rd, Register& Rm) override;
    TranslatedOpcode MOV_reg_rrx(Register& Rd, Register& Rm, uint32_t amount) override;
    TranslatedOpcode MOV_reg_shift_or_rotate(Register& Rd, Register& Rm, ShiftType stype, uint32_t amount) override;
    TranslatedOpcode MOV_imm16(Register& Rd, uint16_t imm16) override;
    TranslatedOpcode MOVT_imm16(Register& Rd, uint16_t imm16) override;
    TranslatedOpcode MOVV_imm32(Register& Rd, uint32_t imm32) override;
    TranslatedOpcode POP_multiple_registers(RegisterList list) override;
    TranslatedOpcode PUSH_multiple_registers(RegisterList list) override;
    TranslatedOpcode STR_imm_offset(Register& Rt, Register& Rn, int16_t imm12) override;
    TranslatedOpcode STR_imm_pre_indexed(Register& Rt, Register& Rn, int16_t imm12) override;
    TranslatedOpcode STR_imm_post_indexed(Register& Rt, Register& Rn, int16_t imm12) override;
    TranslatedOpcode STR_reg_offset(Register& Rt, Register& Rn, Register& Rm, int16_t imm12, int16_t shift = 0) override;
    TranslatedOpcode STR_reg_pre_indexed(Register& Rt, Register& Rn, Register& Rm, int16_t imm12, int16_t shift = 0) override;
    TranslatedOpcode STR_reg_post_indexed(Register& Rt, Register& Rn, Register& Rm, int16_t imm12, int16_t shift = 0) override;
    TranslatedOpcode SUB_reg(Register& Rd, Register& Rn, Register& Rm) override;
    TranslatedOpcode SUB_reg_rrx(Register& Rd, Register& Rn, Register& Rm, uint32_t amount) override;
    TranslatedOpcode SUB_reg_shift_or_rotate(Register& Rd, Register& Rn, Register& Rm, ShiftType stype, uint32_t amount) override;
    TranslatedOpcode SUB_imm12(Register& Rd, Register& Rn, uint16_t imm12) override;

    TranslatedOpcode addLabel(const char* text);
};

}