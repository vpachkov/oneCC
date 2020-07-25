#include "ByteCodeTranslator.h"
#include <cassert>
#include <iostream>

#define NOT_IMPL(x) do { \
    std::cout << "\033[1;31mNOT IMPLEMENTED\033[0m in \033[1;31m" << __FILE__ << "\033[0m\n"; \
    assert(0); \
} while (0)

namespace oneCC::CodeGenerator::X86_32 {

void ByteCodeTranslator::ADC_rm32_reg32(RM op1, Register op2) { NOT_IMPL(); }
void ByteCodeTranslator::ADC_rm8_reg8(RM op1, Register op2) { NOT_IMPL(); }
void ByteCodeTranslator::ADD_AL_imm8(uint8_t op2) { NOT_IMPL(); }
void ByteCodeTranslator::ADD_EAX_imm32(uint32_t op2) { NOT_IMPL(); }
void ByteCodeTranslator::ADD_reg32_rm32(Register op1, RM op2) { NOT_IMPL(); }
void ByteCodeTranslator::ADD_reg8_rm8(Register op1, RM op2) { NOT_IMPL(); }
void ByteCodeTranslator::ADD_rm32_reg32(RM op1, Register op2) { NOT_IMPL(); }
void ByteCodeTranslator::ADD_rm8_reg8(RM op1, Register op2) { NOT_IMPL(); }
void ByteCodeTranslator::OR_AL_imm8(uint8_t op2) { NOT_IMPL(); }
void ByteCodeTranslator::OR_EAX_imm32(uint32_t op2) { NOT_IMPL(); }
void ByteCodeTranslator::OR_reg32_rm32(Register op1, RM op2) { NOT_IMPL(); }
void ByteCodeTranslator::OR_reg8_rm8(Register op1, RM op2) { NOT_IMPL(); }
void ByteCodeTranslator::OR_rm32_reg32(RM op1, Register op2) { NOT_IMPL(); }
void ByteCodeTranslator::OR_rm8_reg8(RM op1, Register op2) { NOT_IMPL(); }
void ByteCodeTranslator::POP_ES() { NOT_IMPL(); }
void ByteCodeTranslator::PUSH_CS() { NOT_IMPL(); }
void ByteCodeTranslator::PUSH_ES() { NOT_IMPL(); }

}