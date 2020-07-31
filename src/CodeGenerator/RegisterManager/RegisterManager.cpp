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

    int RegisterManager::takeSnapshot() {
        m_snapshots.push_back(m_freeRegisters);
        return m_snapshots.size() - 1;
    }

    bool RegisterManager::restoreSnapshot() {
        if (m_snapshots.empty()) {
            return false;
        }
        m_freeRegisters = *m_snapshots.rbegin();
        m_freeRegisters.pop_back();
        return true;
    }

    bool RegisterManager::restoreSnapshot(int snapshot) {
        if (snapshot >= m_snapshots.size()) {
            return false;
        }
        m_freeRegisters = m_snapshots[snapshot];
        return true;
    }

}
