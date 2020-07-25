#pragma once

#include "AbstractAarch32Translator.h"

namespace oneCC::CodeGenerator::Aarch32 {

class AsmTranslator final : public AbstractAarch32Translator {
public:
    AsmTranslator() = default;

    void ADD_imm12(Register Rd, Register Rn, uint16_t imm12) override;
    void BX(Register Rm) override;
    void POP_multiple_registers(RegisterList list) override;
    void PUSH_multiple_registers(RegisterList list) override;
    void SUB_imm12(Register Rd, Register Rn, uint16_t imm12) override;

    void addLabel(const char* text);
};

}