#pragma once

#include <utility>
#include <vector>
#include <map>

namespace oneCC::CodeGenerator {

class RegisterManager {
public:
    RegisterManager() = default;
    explicit RegisterManager(std::vector<int> registers);

    // runtime
    int allocateRegister();
    void freeRegister(int reg);
    bool isFree(int reg);
    void restoreInitialState();
private:
    std::vector<int> m_freeRegisters {};
    std::vector<int> m_initialState {};
};

}
