#include "ByteCodeTranslator.h"

namespace oneCC::CodeGenerator::X86_32 {

void ByteCodeTranslator::ADD_rm8_reg8(RM op1, Register op2) {}
void ByteCodeTranslator::ADD_rm32_reg32(RM op1, Register op2) {}
void ByteCodeTranslator::ADD_reg8_rm8(Register op1, RM op2) {}
void ByteCodeTranslator::ADD_reg32_rm32(Register op1, RM op2) {}
void ByteCodeTranslator::ADD_AL_imm8(uint8_t op2) {}
void ByteCodeTranslator::ADD_EAX_imm32(uint32_t op2) {}
void ByteCodeTranslator::PUSH_ES() {}
void ByteCodeTranslator::POP_ES() {}
void ByteCodeTranslator::OR_rm8_reg8(RM op1, Register op2) {}
void ByteCodeTranslator::OR_rm32_reg32(RM op1, Register op2) {}

}