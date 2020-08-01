#pragma once

#include <functional>
#include <string>
#include <vector>
#include <iostream>

namespace oneCC::CodeGenerator::Aarch32 {

enum RegisterDataType {
    DataVariable,
    DataWriteToVarible,
    DataConst,
    DataMem,
    DataTmp,
};

class RegisterData {
public:
    RegisterData() = default;
    RegisterData(RegisterDataType type, uint32_t value)
        : m_type(type)
        , m_value(value)
    {
    }

    void set(const RegisterData& data)
    {
        m_type = data.m_type;
        m_value = data.m_value;
        m_edited = false;
    }

    // We use markAsTmp when we don't know what kind of data stored where.
    void markAsTmp()
    {
        m_type = DataTmp;
        m_value = 0;
    }

    void dump() const
    {
        static const char* d[] {
            "DataVariable",
            "DataWriteToVarible",
            "DataConst",
            "DataMem",
            "DataTmp",
        };
        std::cout << d[m_type] << " " << m_value << "\n";
    }

    static RegisterData& Tmp()
    {
        static RegisterData data(DataTmp, 0);
        return data;
    }

    bool isSame(const RegisterData& data)
    {
        return m_type == data.m_type && m_value == data.m_value;
    }

    void setEdited(bool edited) { m_edited = edited; }
    bool edited() { return m_edited; }

    RegisterDataType type() { return m_type; }
    uint32_t value() { return m_value; }

private:
    RegisterDataType m_type;
    uint32_t m_value { 0 };
    bool m_edited { false };
};

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
    bad,
};

class Register {
public:
    RegisterAlias alias() const { return m_alias; }
    std::string textAlias();

    RegisterData& data() { return m_data; }

    bool isBad() const { return m_bad; }

    inline bool operator==(const Register& b)
    {
        return alias() == b.alias();
    }

    inline bool operator!=(const Register& b)
    {
        return alias() != b.alias();
    }

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

    static Register& Bad()
    {
        static Register reg(RegisterAlias::bad, true);
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

    Register(RegisterAlias alias, bool bad)
        : m_alias(alias)
        , m_bad(bad)
    {
    }
    Register(Register const&) = delete;
    Register& operator=(Register const&) = delete;
    ~Register() = default;

    RegisterAlias m_alias;
    RegisterData m_data;
    bool m_bad { false };
};

typedef std::vector<std::reference_wrapper<Register>> RegisterList;

}