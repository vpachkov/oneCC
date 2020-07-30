#pragma once

#include "Regs.h"
#include "TypesX86_32.h"

namespace oneCC::CodeGenerator::X86_32 {

enum RMType {
    Reg,
    Mem,
};

class RM final {
public:
    RM(RMType type, int64_t op) : m_type(type), m_opData(op) {}

    bool isReg() { return m_type == Reg; }

    Register reg() { return (Register)m_opData; } // represents enum
    int64_t mem() { return m_opData; } // represents memory location relative to ebp

private:
    RMType m_type;
    int64_t m_opData { 0 };
};

}