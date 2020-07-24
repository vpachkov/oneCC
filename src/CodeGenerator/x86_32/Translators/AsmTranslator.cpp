#include "AsmTranslator.h"

namespace oneCC::CodeGenerator::X86_32 {

void AsmTranslator::ADD_rm8_reg8(RM op1, Register op2) {}
void AsmTranslator::ADD_rm32_reg32(RM op1, Register op2) {}
void AsmTranslator::ADD_reg8_rm8(Register op1, RM op2) {}
void AsmTranslator::ADD_reg32_rm32(Register op1, RM op2) {}
void AsmTranslator::ADD_AL_imm8(uint8_t op2) {}
void AsmTranslator::ADD_EAX_imm32(uint32_t op2) {}
void AsmTranslator::PUSH_ES() {}
void AsmTranslator::POP_ES() {}
void AsmTranslator::OR_rm8_reg8(RM op1, Register op2) {}
void AsmTranslator::OR_rm32_reg32(RM op1, Register op2) {}

}