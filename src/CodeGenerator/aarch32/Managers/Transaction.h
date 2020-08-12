#pragma once

#include "../Common/Regs.h"
#include <cassert>
#include <cstdint>
#include <iostream>

namespace oneCC::CodeGenerator::Aarch32 {

enum TransactionMask {
    GeneralPurposeOnly = 0b11111111111, // defualt, r0-r10 are avail.
    All = 0b111111111111111, // sr0-r15 are avail.
};

struct ReplaceEntry {
    Register& orig;
    Register& with;
};

#define START_FROM_CALLEE_SAVED_REGS 4

// Transaction can be used before every visitNode in code generation
// to control the resources sharing inside this visitNode.
class Transaction {
public:
    friend class TransactionManager;

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
            forbidRegister(pr.orig);
            allowRegister(pr.with);
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

    bool isLogicalUsed(Register& reg) { return m_changedRegisters & (uint32_t)(1 << reg.alias()); }
    bool isPhysicalUsed(Register& reg) { return m_changedRegisters & (uint32_t)(1 << reg.alias()); }

    RegisterList physicallyUsedRegisters(int startReg = 0)
    {
        RegisterList res;

        // A hack to split into 2 cycles to have the right order pushing registers to the stack.
        for (int rega = 11; rega < RegistersCount; rega++) {
            if ((m_changedRegisters & (uint32_t)(1 << rega))) {
                res.push_back(Register::RegisterList()[rega]);
            }
        }

        for (int rega = startReg; rega < 11; rega++) {
            if ((m_changedRegisters & (uint32_t)(1 << rega))) {
                res.push_back(Register::RegisterList()[rega]);
            }
        }

        return res;
    }

    // Logically used registers are registers which have been change their value during the transaction.
    // So, replaced registers are not in this list, since their values will be restored.
    RegisterList logicallyUsedRegisters()
    {
        RegisterList phy = physicallyUsedRegisters();
        RegisterList log;
        
        for (Register& reg : phy) {
            bool notIn = true;
            for (auto replEntry : m_replacedRegisters) {
                if (reg == replEntry.orig) {
                    notIn = false;
                    break;
                }
            }
            if (notIn) {
                log.push_back(reg);
            }
        }

        return log;
    }

    void setTrueBranchLabel(int id) { m_trueBranchLabel = id; }
    void setFalseBranchLabel(int id) { m_falseBranchLabel = id; }

    int trueBranchLabel() { return m_trueBranchLabel; }
    int falseBranchLabel() { return m_falseBranchLabel; }

    int id() { return m_id; }
    uint32_t mask() { return m_mask; }

    static Transaction& Fake()
    {
        static Transaction tr(-1);
        return tr;
    }

private:
    void useRegister(Register& reg) { m_changedRegisters |= (1 << (uint32_t)reg.alias()); }

    int m_id;
    int m_trueBranchLabel { -1 };
    int m_falseBranchLabel { -1 };
    uint32_t m_changedRegisters { 0 };
    uint32_t m_mask;
    RegisterAlias m_resultRegister;
    RegisterAlias m_wantResultResgister;
    std::vector<ReplaceEntry> m_replacedRegisters;
};

}