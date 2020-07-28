#include "RegisterManager.h"
#include <cassert>
#include <iostream>

namespace oneCC::CodeGenerator::Aarch32 {

void RegisterManager::initiateTransaction(bool ignoreForbiddenRegisters)
{
    m_inTransaction = true;
    m_transactions.emplace_back(m_opId++);

    // Forbid registers which have been forbidden in prev transaction
    if (!ignoreForbiddenRegisters && m_transactions.size() > 1) {
        uint32_t mask = m_transactions[m_transactions.size() - 2].mask();
        m_transactions.back().setWhiteListRegisters(mask);
    }
}

Transaction& RegisterManager::activeTransaction()
{
    return m_transactions.back();
}

void RegisterManager::didTransaction()
{
    m_transactions.pop_back();
    m_inTransaction = !m_transactions.empty();
}

Register& RegisterManager::chooseRegister()
{
    uint32_t mask = (uint32_t)TransactionMask::GeneralPurposeOnly;
    if (m_inTransaction) {
        mask = activeTransaction().mask();
    }

    for (int reg = 0; reg < RegistersCount; reg++) {
        if ((mask & (uint32_t)(1 << reg)) > 0) {
            return Register::RegisterList()[reg];
        }
    }

    assert(0 && "No regs found");
    return Register::Bad();
}

Register& RegisterManager::chooseRegister(const RegisterData& data)
{
    uint32_t mask = (uint32_t)TransactionMask::GeneralPurposeOnly;
    if (m_inTransaction) {
        mask = activeTransaction().mask();
    }

    for (int reg = RegistersCount - 1; reg >= 0; reg--) {
        Register& tmpreg = Register::RegisterList()[reg];
        if ((mask & (uint32_t)(1 << reg)) > 0) {
            if (tmpreg.data().isSame(data)) {
                return Register::RegisterList()[reg];
            }
        }
    }

    for (int reg = 0; reg < RegistersCount; reg++) {
        if ((mask & (uint32_t)(1 << reg)) > 0) {
            return Register::RegisterList()[reg];
        }
    }

    assert(0 && "No regs found");
    return Register::Bad();
}

int RegisterManager::save(Register& reg, const RegisterData& data)
{
    assert((!reg.isBad()));
    uint32_t mask = (uint32_t)TransactionMask::All;
    if (m_inTransaction) {
        mask = activeTransaction().mask();
    }

    if ((mask & (uint32_t)(1 << (uint32_t)reg.alias())) > 0) {
        reg.data().set(data);
        return 0;
    }

    return -1;
}

Register& RegisterManager::has(const RegisterData& data)
{
    for (int reg = 0; reg < RegistersCount; reg++) {
        Register& tmpreg = Register::RegisterList()[reg];
        if (tmpreg.data().isSame(data)) {
            return Register::RegisterList()[reg];
        }
    }
    return Register::Bad();
}

}