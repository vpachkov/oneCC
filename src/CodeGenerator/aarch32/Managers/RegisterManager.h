#pragma once

#include "../Common/Regs.h"
#include <vector>

namespace oneCC::CodeGenerator::Aarch32 {

class CodeGeneratorAarch32;

class RegisterManager {
public:
    RegisterManager(CodeGeneratorAarch32& codeGen);

    bool canUse(const Register& reg);
    Register& chooseRegister();
    Register& chooseRegister(const RegisterData& data);
    Register& chooseRegisterFromBack();
    int resolveForbiddenRegister(Register& reg);

    int put(Register& reg, const RegisterData& data);
    Register& has(const RegisterData& data);

private:
    CodeGeneratorAarch32& m_codeGenerator;
};

}