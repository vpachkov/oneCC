#pragma once

#include "AbstractX86_32Translator.h"

namespace oneCC::CodeGenerator::X86_32 {

class ByteCodeTranslator final : public AbstractX86_32Translator {
public:
    ByteCodeTranslator() = default;

    // Generated (test part)
    void ADC_rm32_reg32(RM op1, Register op2) override ;
    void ADC_rm8_reg8(RM op1, Register op2) override ;
    void ADD_AL_imm8(uint8_t op2) override ;
    void ADD_EAX_imm32(uint32_t op2) override ;
    void ADD_reg32_rm32(Register op1, RM op2) override ;
    void ADD_reg8_rm8(Register op1, RM op2) override ;
    void ADD_rm32_reg32(RM op1, Register op2) override ;
    void ADD_rm8_reg8(RM op1, Register op2) override ;
    void OR_AL_imm8(uint8_t op2) override ;
    void OR_EAX_imm32(uint32_t op2) override ;
    void OR_reg32_rm32(Register op1, RM op2) override ;
    void OR_reg8_rm8(Register op1, RM op2) override ;
    void OR_rm32_reg32(RM op1, Register op2) override ;
    void OR_rm8_reg8(RM op1, Register op2) override ;
    void POP_ES() override ;
    void PUSH_CS() override ;
    void PUSH_ES() override ;

};

}