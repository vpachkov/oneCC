#include "RegisterManager.h"
#include <string>

namespace oneCC::CodeGenerator {

RegisterManager::RegisterManager(std::vector<int> registers)
    : m_freeRegisters(registers)
    , m_initialState(std::move(registers)) {}

int RegisterManager::allocateRegister() {
    if (m_freeRegisters.empty()){
        return 0;
    }
    int reg =  m_freeRegisters.back();
    m_freeRegisters.pop_back();
    return reg;
}

void RegisterManager::freeRegister(int reg) {
    m_freeRegisters.push_back(reg);
}

bool RegisterManager::isFree(int reg) {
    for (auto& freeReg : m_freeRegisters) {
        if (freeReg == reg) {
            return true;
        }
    }
    return false;
}

void RegisterManager::restoreInitialState() {
    m_freeRegisters = m_initialState;
}

}
