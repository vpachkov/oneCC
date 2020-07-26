#pragma once

#include <functional>
#include <string>
#include <vector>

namespace oneCC::CodeGenerator::Aarch32 {

const int RegistersCount = 15;

enum RegisterAlias {
    r0,
    r1,
    r2,
    r3,
    r4,
    r5,
    r6,
    r7,
    r8,
    r9,
    r10,
    fp,
    ip,
    sp,
    lr,
    pc,
};

class Register {
public:
    RegisterAlias alias() const { return m_alias; }
    std::string textAlias();

    // All 15 registers of a machine :^)
    static Register& R0()
    {
        static Register reg(RegisterAlias::r0);
        return reg;
    }

    static Register& R1()
    {
        static Register reg(RegisterAlias::r1);
        return reg;
    }

    static Register& R2()
    {
        static Register reg(RegisterAlias::r2);
        return reg;
    }

    static Register& R3()
    {
        static Register reg(RegisterAlias::r3);
        return reg;
    }

    static Register& R4()
    {
        static Register reg(RegisterAlias::r4);
        return reg;
    }

    static Register& R5()
    {
        static Register reg(RegisterAlias::r5);
        return reg;
    }

    static Register& R6()
    {
        static Register reg(RegisterAlias::r6);
        return reg;
    }

    static Register& R7()
    {
        static Register reg(RegisterAlias::r7);
        return reg;
    }

    static Register& R8()
    {
        static Register reg(RegisterAlias::r8);
        return reg;
    }

    static Register& R9()
    {
        static Register reg(RegisterAlias::r9);
        return reg;
    }

    static Register& R10()
    {
        static Register reg(RegisterAlias::r10);
        return reg;
    }

    static Register& FP()
    {
        static Register reg(RegisterAlias::fp);
        return reg;
    }

    static Register& IP()
    {
        static Register reg(RegisterAlias::ip);
        return reg;
    }

    static Register& SP()
    {
        static Register reg(RegisterAlias::sp);
        return reg;
    }

    static Register& LR()
    {
        static Register reg(RegisterAlias::lr);
        return reg;
    }

    static Register& PC()
    {
        static Register reg(RegisterAlias::pc);
        return reg;
    }

    static std::vector<std::reference_wrapper<Register>>& RegisterList()
    {
        static std::vector<std::reference_wrapper<Register>> m_regs {
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
        return m_regs;
    }

private:
    Register(RegisterAlias alias)
        : m_alias(alias)
    {
    }
    Register(Register const&) = delete;
    Register& operator=(Register const&) = delete;
    ~Register() = default;

    RegisterAlias m_alias;
};

typedef std::vector<std::reference_wrapper<Register>> RegisterList;

}