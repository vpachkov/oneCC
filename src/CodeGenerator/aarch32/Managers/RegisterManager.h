#pragma once

#include "../Common/Regs.h"

namespace oneCC::CodeGenerator::Aarch32 {

class RegisterManager {
public:
    RegisterManager()
    {
        m_regs = {
            Register::R0(),
            Register::R1(),
            Register::R2(),
            Register::R3(),
            Register::R4(),
            Register::R5(),
            Register::R6(),
            Register::R7(),
            Register::R8(),
            Register::R9(),
            Register::R10(),
            Register::FP(),
            Register::IP(),
            Register::SP(),
            Register::LR(),
            Register::PC()
        };
    }

    int allocateRegister();
    int freeRegister();

private:
    RegisterList m_regs;
};

}