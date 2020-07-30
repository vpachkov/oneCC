#include "RegisterManager.h"
#include "../CodeGenerator.h"
#include <cassert>
#include <iostream>

namespace oneCC::CodeGenerator::Aarch32 {

RegisterManager::RegisterManager(CodeGeneratorAarch32& codeGen)
    : m_codeGenerator(codeGen)
{
}

// Returns if the register can be used in this transaction.
bool RegisterManager::canUse(const Register& reg)
{
    uint32_t mask = (uint32_t)TransactionMask::GeneralPurposeOnly;
    if (m_codeGenerator.transactionManager().in()) {
        mask = m_codeGenerator.transactionManager().active().mask();
    }

    return (mask & (uint32_t)(1 << reg.alias()));
}

// This is a bad solution, we need to plan this in advance.
int RegisterManager::resolveForbiddenRegister(Register& reg)
{
    if (canUse(reg)) {
        return 0;
    }
    Register& with = chooseRegisterFromBack();
    m_codeGenerator.transactionManager().active().replaceForbidRegister(reg, with);
    m_codeGenerator.translator().MOV_reg(with, reg);
    replace(with, reg.data());
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

// Looks if a register has such data and returns if so, or return other register.
Register& RegisterManager::chooseRegister(const RegisterData& data)
{
    for (int reg = RegistersCount - 1; reg >= 0; reg--) {
        Register& tmpreg = Register::RegisterList()[reg];
        if (canUse(tmpreg)) {
            if (tmpreg.data().isSame(data)) {
                return Register::RegisterList()[reg];
            }
        }
    }

    return chooseRegister();
}

// Replace the original register data with a new one
int RegisterManager::replace(Register& reg, const RegisterData& data)
{
    assert((!reg.isBad()));

    if (canUse(reg)) {
        if (reg.data().type() == DataTmp) {
            return 0;
        }

        if (reg.data().isSame(data)) {
            return 1;
        }
        
        if (reg.data().type() == DataVariable && reg.data().edited()) {
            int offset = m_codeGenerator.varManager().getOffset(reg.data().value());
            m_codeGenerator.translator().STR_imm_offset(reg, Register::FP(), -offset);
        }

        if (reg.data().type() == DataMem && reg.data().edited()) {
            int offset = m_codeGenerator.varManager().getOffset(reg.data().value());
            std::cout << "TODO: store at mem " << reg.data().value() << "\n";;
        }
        
        reg.data().set(data);
        return 0;
    }

    return -1;
}

// Write works in 2 cases.
// 1) We write a new value to a varible and the register is used as a cache. With replace it will be swapped back to the stack.
// 2) We write a new value to a place at mem and the register is used as a cache. With replace it will be swapped back to the mem.
int RegisterManager::write(Register& reg)
{
    assert((!reg.isBad()));

    if (canUse(reg)) {
        if (reg.data().type() == DataVariable) {
            reg.data().setEdited(true);
            return 0;
        }

        if (reg.data().type() == DataMem) {
            reg.data().setEdited(true);
            return 0;
        }

       return -1;
    }

    return -1;
}

// Returns if there is a register with such data.
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