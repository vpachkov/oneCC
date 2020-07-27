#include "RegisterManager.h"
#include <cassert>
#include <iostream>

namespace oneCC::CodeGenerator::Aarch32 {

Transaction& RegisterManager::initiateTransaction(bool ignoreForbiddenRegisters)
{
    m_inTransaction = true;
    m_transactions.emplace_back(m_opId++);

    // Forbid registers which have been forbidden in prev transaction
    if (!ignoreForbiddenRegisters && m_transactions.size() > 1) {
        uint32_t mask = m_transactions[m_transactions.size() - 2].mask();
        m_transactions.back().setWhiteListRegisters(mask);
    }

    return m_transactions.back();
}

Transaction& RegisterManager::activeTransaction()
{
    return m_transactions.back();
}

void RegisterManager::didTransaction(Transaction& trans)
{
    assert(m_transactions.back().id() == trans.id() && "Should be ended in stack order");
    m_transactions.pop_back();
    m_inTransaction = m_transactions.empty();
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
    return Register::RegisterList()[0];
}

}