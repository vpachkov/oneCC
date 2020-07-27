#pragma once

#include "../Common/Regs.h"
#include <cassert>
#include <iostream>
#include <cstdint>

namespace oneCC::CodeGenerator::Aarch32 {

enum TransactionMask {
    GeneralPurposeOnly = 0b1111111111, // defualt, r0-r10 are avail.
    All = 0b111111111111111, // sr0-r15 are avail.
};

class Transaction {
public:
    Transaction(int id)
        : m_id(id)
        , m_mask((uint32_t)GeneralPurposeOnly)
    {
    }

    void setWhiteListRegisters(uint32_t mask) { m_mask = mask; }
    void setWhiteListRegisters(TransactionMask mask) { m_mask = (uint32_t)mask; }
    
    void forbidRegister(const Register& reg)
    {
        uint32_t tmp = 1 << (uint32_t)reg.alias();
        m_mask &= ~tmp;
    }

    void forbidRegisters(RegisterList regList)
    {
        for (Register& reg : regList) {
            uint32_t tmp = 1 << (uint32_t)reg.alias();
            m_mask &= ~tmp;
        }
    }

    void setResultRegister(const Register& reg) { 
        m_resultRegister = reg.alias(); 
    }
    
    Register& getResultRegister() 
    { 
        assert((uint32_t)m_resultRegister < RegistersCount);
        return Register::RegisterList()[(uint32_t)m_resultRegister]; 
    }

    int id() { return m_id; }
    uint32_t mask() { return m_mask; }

private:
    int m_id;
    uint32_t m_mask;
    RegisterAlias m_resultRegister;
};

}