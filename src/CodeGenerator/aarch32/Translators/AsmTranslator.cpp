#include "AsmTranslator.h"
#include <cassert>
#include <iostream>

#define NOT_IMPL(x)                                                                               \
    do {                                                                                          \
        std::cout << "\033[1;31mNOT IMPLEMENTED\033[0m in \033[1;31m" << __FILE__ << "\033[0m\n"; \
        assert(0);                                                                                \
    } while (0)

namespace oneCC::CodeGenerator::Aarch32 {

void AsmTranslator::ADD_reg(Register& Rd, Register& Rn, Register& Rm)
{
    std::cout << "add " << Rd.textAlias() << ", " << Rn.textAlias() << ", " << Rm.textAlias() << "\n";
}

void AsmTranslator::ADD_reg_rrx(Register& Rd, Register& Rn, Register& Rm, uint32_t amount)
{
    std::cout << "add " << Rd.textAlias() << ", " << Rn.textAlias() << ", " << Rm.textAlias() << ", (rrx)" << amount << "\n";
}

void AsmTranslator::ADD_reg_shift_or_rotate(Register& Rd, Register& Rn, Register& Rm, ShiftType stype, uint32_t amount)
{
    amount &= 31;
    std::cout << "add " << Rd.textAlias() << ", " << Rn.textAlias() << ", " << Rm.textAlias() << ", " << stype << ", #" << amount << "\n";
}

void AsmTranslator::ADD_imm12(Register& Rd, Register& Rn, uint16_t imm12)
{
    imm12 = imm12 & 0xfff; // making it 12bit long
    std::cout << "add " << Rd.textAlias() << ", " << Rn.textAlias() << ", #" << imm12 << "\n";
}

void AsmTranslator::BX(Register& Rm)
{
    std::cout << "bx " << Rm.textAlias() << "\n";
}

void AsmTranslator::MOV_reg(Register& Rd, Register& Rm)
{
    std::cout << "mov " << Rd.textAlias() << ", " << Rm.textAlias() << "\n";
}
void AsmTranslator::MOV_reg_rrx(Register& Rd, Register& Rm, uint32_t amount)
{
    std::cout << "mov " << Rd.textAlias() << ", " << Rm.textAlias() << ", (rrx)" << amount << "\n";
}
void AsmTranslator::MOV_reg_shift_or_rotate(Register& Rd, Register& Rm, ShiftType stype, uint32_t amount)
{
    amount &= 31;
    std::cout << "mov " << Rd.textAlias() << ", " << Rm.textAlias() << ", " << stype << ", #" << amount << "\n";
}

void AsmTranslator::MOV_imm16(Register& Rd, uint16_t imm16)
{
    std::cout << "mov " << Rd.textAlias() << " " << (int)imm16 << "\n";
}

void AsmTranslator::MOVT_imm16(Register& Rd, uint16_t imm16)
{
    std::cout << "movt " << Rd.textAlias() << " " << (int)imm16 << "\n";
}

void AsmTranslator::MOVV_imm32(Register& Rd, uint32_t imm32)
{
    std::cout << "mov " << Rd.textAlias() << " " << (int)imm32 << " @virt\n";
}

void AsmTranslator::POP_multiple_registers(RegisterList list)
{
    std::cout << "pop { ";
    for (Register& reg : list) {
        std::cout << reg.textAlias() << " ";
    }
    std::cout << "}\n";
}

void AsmTranslator::PUSH_multiple_registers(RegisterList list)
{
    std::cout << "push { ";
    for (Register& reg : list) {
        std::cout << reg.textAlias() << " ";
    }
    std::cout << "}\n";
}

void AsmTranslator::STR_imm_offset(Register& Rt, Register& Rn, int16_t imm12)
{
    std::cout << "str " << Rt.textAlias() << ", [" << Rn.textAlias() << ", #" << int(imm12) << "]\n";
}

void AsmTranslator::STR_imm_pre_indexed(Register& Rt, Register& Rn, int16_t imm12)
{
    std::cout << "str " << Rt.textAlias() << ", [" << Rn.textAlias() << ", #" << int(imm12) << "]!\n";
}

void AsmTranslator::STR_imm_post_indexed(Register& Rt, Register& Rn, int16_t imm12)
{
    std::cout << "str " << Rt.textAlias() << ", [" << Rn.textAlias() << "], #" << int(imm12) << "\n";
}

void AsmTranslator::STR_reg_offset(Register& Rt, Register& Rn, Register& Rm, int16_t imm12, int16_t shift)
{
    std::cout << "str " << Rt.textAlias() << ", [" << Rn.textAlias() << ", " << Rm.textAlias() << ", " << shift << "]\n";
}

void AsmTranslator::STR_reg_pre_indexed(Register& Rt, Register& Rn, Register& Rm, int16_t imm12, int16_t shift)
{
    std::cout << "str " << Rt.textAlias() << ", [" << Rn.textAlias() << ", " << Rm.textAlias() << ", " << shift << "]!\n";
}

void AsmTranslator::STR_reg_post_indexed(Register& Rt, Register& Rn, Register& Rm, int16_t imm12, int16_t shift)
{
    std::cout << "str " << Rt.textAlias() << ", [" << Rn.textAlias() << "], " << Rm.textAlias() << ", " << shift << "\n";
}

void AsmTranslator::SUB_imm12(Register& Rd, Register& Rn, uint16_t imm12)
{
    imm12 = imm12 & 0xfff; // making it 12bit long
    std::cout << "sub " << Rd.textAlias() << ", " << Rn.textAlias() << ", #" << imm12 << "\n";
}

void AsmTranslator::addLabel(const char* text)
{
    std::cout << text << "\n";
}

}