#pragma once

#include "../Common/Regs.h"
#include <cassert>
#include <cstdint>
#include <iostream>

namespace oneCC::CodeGenerator::Aarch32 {

enum TransactionMask {
    GeneralPurposeOnly = 0b1111111111, // defualt, r0-r10 are avail.
    All = 0b111111111111111, // sr0-r15 are avail.
};

// Transaction can be used before every visitNode in code generation
// to control the resources sharing inside this visitNode.
class Transaction {
public:
    Transaction(int id)
        : m_id(id)
        , m_mask((uint32_t)GeneralPurposeOnly)
        , m_replacedRegisters()
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

    void allowRegister(const Register& reg)
    {
        uint32_t tmp = 1 << (uint32_t)reg.alias();
        m_mask |= tmp;
    }

    void replaceForbidRegister(Register& target, Register& with)
    {
        m_replacedRegisters.push_back({ target, with });
        allowRegister(target);
        forbidRegister(with);
    }

    template <typename Callback>
    void restoreReplaces(Callback callback)
    {
        while (!m_replacedRegisters.empty()) {
            auto pr = m_replacedRegisters.back();
            callback(pr);
            forbidRegister(pr.first);
            allowRegister(pr.second);
            m_replacedRegisters.pop_back();
        }
    }

    void setWillingResultRegister(const Register& reg)
    {
        m_wantResultResgister = reg.alias();
    }

    void setResultRegister(const Register& reg)
    {
        m_resultRegister = reg.alias();
    }

    Register& resultRegister()
    {
        assert((uint32_t)m_resultRegister < RegistersCount);
        return Register::RegisterList()[(uint32_t)m_resultRegister];
    }

    void setTrueBranchInstrId(int id) { m_trueBranchInstrId = id; }
    void setFalseBranchInstrId(int id) { m_falseBranchInstrId = id; }

    int trueBranchInstrId() { return m_trueBranchInstrId; }
    int falseBranchInstrId() { return m_falseBranchInstrId; }

    int id() { return m_id; }
    uint32_t mask() { return m_mask; }

    static Transaction& Fake()
    {
        static Transaction tr(-1);
        return tr;
    }

private:
    int m_id;
    int m_trueBranchInstrId { -1 };
    int m_falseBranchInstrId { -1 };
    uint32_t m_mask;
    RegisterAlias m_resultRegister;
    RegisterAlias m_wantResultResgister;
    std::vector<std::pair<Register&, Register&>> m_replacedRegisters;
};

}