#include "AsmTranslator.h"
#include <cassert>
#include <iostream>

#define NOT_IMPL(x)                                                                            \
    do {                                                                                       \
        std::cout + "\033[1;31mNOT IMPLEMENTED\033[0m in \033[1;31m" + __FILE__ + "\033[0m\n"; \
        assert(0);                                                                             \
    } while (0)

namespace oneCC::CodeGenerator::Aarch32 {

TranslatedOpcode AsmTranslator::ADD_reg(Register& Rd, Register& Rn, Register& Rm)
{
    return TranslatedOpcode("add " + Rd.textAlias() + ", " + Rn.textAlias() + ", " + Rm.textAlias());
}

TranslatedOpcode AsmTranslator::ADD_reg_rrx(Register& Rd, Register& Rn, Register& Rm, uint32_t amount)
{
    return TranslatedOpcode("add " + Rd.textAlias() + ", " + Rn.textAlias() + ", " + Rm.textAlias() + ", (rrx)" + std::to_string(amount));
}

TranslatedOpcode AsmTranslator::ADD_reg_shift_or_rotate(Register& Rd, Register& Rn, Register& Rm, ShiftType stype, uint32_t amount)
{
    amount &= 31;
    return TranslatedOpcode("add " + Rd.textAlias() + ", " + Rn.textAlias() + ", " + Rm.textAlias() + ", " + std::to_string((int)stype) + ", #" + std::to_string(amount));
}

TranslatedOpcode AsmTranslator::ADD_imm12(Register& Rd, Register& Rn, uint16_t imm12)
{
    imm12 = imm12 & 0xfff; // making it 12bit long
    return TranslatedOpcode("add " + Rd.textAlias() + ", " + Rn.textAlias() + ", #" + std::to_string(imm12));
}

TranslatedOpcode AsmTranslator::BL(uint32_t imm24, const std::string& label)
{
    return TranslatedOpcode("bl", label);
}

TranslatedOpcode AsmTranslator::BLX(uint32_t imm24, const std::string& label)
{
    return TranslatedOpcode("blx", label);
}

TranslatedOpcode AsmTranslator::BX(Register& Rm)
{
    return TranslatedOpcode("bx " + Rm.textAlias());
}

TranslatedOpcode AsmTranslator::LDR_imm_offset(Register& Rt, Register& Rn, int16_t imm12)
{
    return TranslatedOpcode("ldr " + Rt.textAlias() + ", [" + Rn.textAlias() + ", #" + std::to_string(int(imm12)) + "]");
}

TranslatedOpcode AsmTranslator::LDR_imm_pre_indexed(Register& Rt, Register& Rn, int16_t imm12)
{
    return TranslatedOpcode("ldr " + Rt.textAlias() + ", [" + Rn.textAlias() + ", #" + std::to_string(int(imm12)) + "]!");
}

TranslatedOpcode AsmTranslator::LDR_imm_post_indexed(Register& Rt, Register& Rn, int16_t imm12)
{
    return TranslatedOpcode("ldr " + Rt.textAlias() + ", [" + Rn.textAlias() + "], #" + std::to_string(int(imm12)));
}

TranslatedOpcode AsmTranslator::LDR_reg_offset(Register& Rt, Register& Rn, Register& Rm, int16_t imm12, int16_t shift)
{
    return TranslatedOpcode("ldr " + Rt.textAlias() + ", [" + Rn.textAlias() + ", " + Rm.textAlias() + ", " + std::to_string(shift) + "]");
}

TranslatedOpcode AsmTranslator::LDR_reg_pre_indexed(Register& Rt, Register& Rn, Register& Rm, int16_t imm12, int16_t shift)
{
    return TranslatedOpcode("ldr " + Rt.textAlias() + ", [" + Rn.textAlias() + ", " + Rm.textAlias() + ", " + std::to_string(shift) + "]!");
}

TranslatedOpcode AsmTranslator::LDR_reg_post_indexed(Register& Rt, Register& Rn, Register& Rm, int16_t imm12, int16_t shift)
{
    return TranslatedOpcode("ldr " + Rt.textAlias() + ", [" + Rn.textAlias() + "], " + Rm.textAlias() + ", " + std::to_string(shift));
}

TranslatedOpcode AsmTranslator::MOV_reg(Register& Rd, Register& Rm)
{
    return TranslatedOpcode("mov " + Rd.textAlias() + ", " + Rm.textAlias());
}
TranslatedOpcode AsmTranslator::MOV_reg_rrx(Register& Rd, Register& Rm, uint32_t amount)
{
    return TranslatedOpcode("mov " + Rd.textAlias() + ", " + Rm.textAlias() + ", (rrx)" + std::to_string(amount));
}
TranslatedOpcode AsmTranslator::MOV_reg_shift_or_rotate(Register& Rd, Register& Rm, ShiftType stype, uint32_t amount)
{
    amount &= 31;
    return TranslatedOpcode("mov " + Rd.textAlias() + ", " + Rm.textAlias() + ", " + std::to_string((int)stype) + ", #" + std::to_string(amount));
}

TranslatedOpcode AsmTranslator::MOV_imm16(Register& Rd, uint16_t imm16)
{
    return TranslatedOpcode("mov " + Rd.textAlias() + ", #" + std::to_string((int)imm16));
}

TranslatedOpcode AsmTranslator::MOVT_imm16(Register& Rd, uint16_t imm16)
{
    return TranslatedOpcode("movt " + Rd.textAlias() + ", #" + std::to_string((int)imm16));
}

TranslatedOpcode AsmTranslator::MOVV_imm32(Register& Rd, uint32_t imm32)
{
    return TranslatedOpcode("mov " + Rd.textAlias() + ", #" + std::to_string((int)imm32) + " @virt");
}

TranslatedOpcode AsmTranslator::POP_multiple_registers(RegisterList list)
{
    std::string s("pop { ");
    for (Register& reg : list) {
        s += reg.textAlias() + " ";
    }
    s += "}";
    return TranslatedOpcode(std::move(s));
}

TranslatedOpcode AsmTranslator::PUSH_multiple_registers(RegisterList list)
{
    std::string s("push { ");
    for (Register& reg : list) {
        s += reg.textAlias() + " ";
    }
    s += "}";
    return TranslatedOpcode(std::move(s));
}

TranslatedOpcode AsmTranslator::STR_imm_offset(Register& Rt, Register& Rn, int16_t imm12)
{
    return TranslatedOpcode("str " + Rt.textAlias() + ", [" + Rn.textAlias() + ", #" + std::to_string(int(imm12)) + "]");
}

TranslatedOpcode AsmTranslator::STR_imm_pre_indexed(Register& Rt, Register& Rn, int16_t imm12)
{
    return TranslatedOpcode("str " + Rt.textAlias() + ", [" + Rn.textAlias() + ", #" + std::to_string(int(imm12)) + "]!");
}

TranslatedOpcode AsmTranslator::STR_imm_post_indexed(Register& Rt, Register& Rn, int16_t imm12)
{
    return TranslatedOpcode("str " + Rt.textAlias() + ", [" + Rn.textAlias() + "], #" + std::to_string(int(imm12)));
}

TranslatedOpcode AsmTranslator::STR_reg_offset(Register& Rt, Register& Rn, Register& Rm, int16_t imm12, int16_t shift)
{
    return TranslatedOpcode("str " + Rt.textAlias() + ", [" + Rn.textAlias() + ", " + Rm.textAlias() + ", " + std::to_string(shift) + "]");
}

TranslatedOpcode AsmTranslator::STR_reg_pre_indexed(Register& Rt, Register& Rn, Register& Rm, int16_t imm12, int16_t shift)
{
    return TranslatedOpcode("str " + Rt.textAlias() + ", [" + Rn.textAlias() + ", " + Rm.textAlias() + ", " + std::to_string(shift) + "]!");
}

TranslatedOpcode AsmTranslator::STR_reg_post_indexed(Register& Rt, Register& Rn, Register& Rm, int16_t imm12, int16_t shift)
{
    return TranslatedOpcode("str " + Rt.textAlias() + ", [" + Rn.textAlias() + "], " + Rm.textAlias() + ", " + std::to_string(shift));
}

TranslatedOpcode AsmTranslator::SUB_reg(Register& Rd, Register& Rn, Register& Rm)
{
    return TranslatedOpcode("sub " + Rd.textAlias() + ", " + Rn.textAlias() + ", " + Rm.textAlias());
}

TranslatedOpcode AsmTranslator::SUB_reg_rrx(Register& Rd, Register& Rn, Register& Rm, uint32_t amount)
{
    return TranslatedOpcode("sub " + Rd.textAlias() + ", " + Rn.textAlias() + ", " + Rm.textAlias() + ", (rrx)" + std::to_string(amount));
}

TranslatedOpcode AsmTranslator::SUB_reg_shift_or_rotate(Register& Rd, Register& Rn, Register& Rm, ShiftType stype, uint32_t amount)
{
    amount &= 31;
    return TranslatedOpcode("sub " + Rd.textAlias() + ", " + Rn.textAlias() + ", " + Rm.textAlias() + ", " + std::to_string((int)stype) + ", #" + std::to_string(amount));
}

TranslatedOpcode AsmTranslator::SUB_imm12(Register& Rd, Register& Rn, uint16_t imm12)
{
    imm12 = imm12 & 0xfff; // making it 12bit long
    return TranslatedOpcode("sub " + Rd.textAlias() + ", " + Rn.textAlias() + ", #" + std::to_string(imm12));
}

TranslatedOpcode AsmTranslator::addLabel(const char* text)
{
    return TranslatedOpcode(text);
}

}