#pragma once

#include "Regs.h"
#include <cstdint>

namespace oneCC::CodeGenerator::X86_32 {

enum RMType {
    Reg,
    Mem,
};

class RM final {
public:
    RM(RMType type, uint8_t op)
    {
        m_type = type;
        m_opData = op;
        m_opSize = sizeof(op);
    }

    RM(RMType type, uint16_t op)
    {
        m_type = type;
        m_opData = op;
        m_opSize = sizeof(op);
    }

    RM(RMType type, uint32_t op)
    {
        m_type = type;
        m_opData = op;
        m_opSize = sizeof(op);
    }

    bool isReg() { return m_type == Reg; }
    bool isMem() { return m_type == Mem; }
    bool is8()  { return m_opSize == 1; }
    bool is16() { return m_opSize == 2; }
    bool is32() { return m_opSize == 4; }
    int opSize() { return m_opSize; }

    Register reg() { return (Register)m_opData; }
    uint32_t  mem() { return m_opData; }

private:
    RMType m_type;
    uint32_t m_opSize { 0 };
    uint32_t m_opData { 0 };
};

}