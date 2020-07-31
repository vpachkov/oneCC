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
    int takeSnapshot();
    bool restoreSnapshot(int snapshot);
    bool restoreSnapshot();
private:
    std::vector<int> m_freeRegisters {};
    std::vector<int> m_initialState {};

    std::vector<std::vector<int>> m_snapshots {};
};

}
