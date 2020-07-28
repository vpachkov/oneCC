#include "RegisterManager.h"
#include "../CodeGenerator.h"
#include <cassert>
#include <iostream>

namespace oneCC::CodeGenerator::Aarch32 {

RegisterManager::RegisterManager(CodeGeneratorAarch32& codeGen)
    : m_codeGenerator(codeGen)
{
}

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
    assert(!m_transactions.empty());

    m_transactions.back().restoreReplaces([&](std::pair<Register&, Register&>& replace) {
        m_codeGenerator.translator().MOV_reg(replace.first, replace.second);
        put(replace.first, replace.first.data());
    });

    m_transactions.pop_back();
    m_inTransaction = !m_transactions.empty();
}

bool RegisterManager::canUse(const Register& reg)
{
    uint32_t mask = (uint32_t)TransactionMask::GeneralPurposeOnly;
    if (m_inTransaction) {
        mask = activeTransaction().mask();
    }

    return ((mask & (uint32_t)(1 << reg.alias())) > 0);
}

// This is a bad solution, we need to plan this in advance.
int RegisterManager::resolveForbiddenRegister(Register& reg)
{
    if (canUse(reg)) {
        return 0;
    }
    Register& with = chooseRegisterFromBack();
    activeTransaction().replaceForbidRegister(reg, with);
    m_codeGenerator.translator().MOV_reg(with, reg);
    put(with, reg.data());
    return 0;
}

Register& RegisterManager::chooseRegister()
{
    for (int reg = 0; reg < RegistersCount; reg++) {
        Register& tmpreg = Register::RegisterList()[reg];
        if (canUse(tmpreg)) {
            return tmpreg;
        }
    }

    assert(0 && "No regs found");
    return Register::Bad();
}

Register& RegisterManager::chooseRegisterFromBack()
{
    for (int reg = RegistersCount - 1; reg >= 0; reg--) {
        Register& tmpreg = Register::RegisterList()[reg];
        if (canUse(tmpreg)) {
            return tmpreg;
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
        if (canUse(tmpreg)) {
            if (tmpreg.data().isSame(data)) {
                return Register::RegisterList()[reg];
            }
        }
    }

    for (int reg = 0; reg < RegistersCount; reg++) {
        Register& tmpreg = Register::RegisterList()[reg];
        if (canUse(tmpreg)) {
            return tmpreg;
        }
    }

    assert(0 && "No regs found");
    return Register::Bad();
}

int RegisterManager::put(Register& reg, const RegisterData& data)
{
    assert((!reg.isBad()));

    if (canUse(reg)) {
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