#pragma once

#include <vector>


class RegisterManager {
public:
    int allocateRegister();
    int freeRegister();
private:
    std::vector<int>registers {};
};
