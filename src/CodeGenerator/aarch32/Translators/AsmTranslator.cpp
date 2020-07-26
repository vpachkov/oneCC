#include "AsmTranslator.h"
#include <cassert>
#include <iostream>

#define NOT_IMPL(x) do { \
    std::cout << "\033[1;31mNOT IMPLEMENTED\033[0m in \033[1;31m" << __FILE__ << "\033[0m\n"; \
    assert(0); \
} while (0)

namespace oneCC::CodeGenerator::Aarch32 {

void AsmTranslator::ADD_imm12(Register& Rd, Register& Rn, uint16_t imm12)
{
    imm12 = imm12 & 0xfff; // making it 12bit long
    std::cout << "add " << Rd.textAlias() << ", " << Rn.textAlias() << ", #" << imm12 << "\n";
}


void AsmTranslator::BX(Register& Rm)
{
    std::cout << "bx " << Rm.textAlias() << "\n";
}

// TODO: output to file?
void AsmTranslator::POP_multiple_registers(RegisterList list)
{
    std::cout << "pop { ";
    for (Register& reg : list) {
        std::cout << reg.textAlias() << " ";
    }
    std::cout << "}\n";
}

// TODO: output to file?
void AsmTranslator::PUSH_multiple_registers(RegisterList list)
{
    std::cout << "push { ";
    for (Register& reg : list) {
        std::cout << reg.textAlias() << " ";
    }
    std::cout << "}\n";
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