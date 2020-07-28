#pragma once

#include "../Common/Regs.h"
#include "Transaction.h"
#include <vector>

namespace oneCC::CodeGenerator::Aarch32 {

class CodeGeneratorAarch32;

class RegisterManager {
public:
    RegisterManager(CodeGeneratorAarch32& codeGen);

    void initiateTransaction(bool ignoreForbiddenRegisters = false);
    Transaction& activeTransaction();
    void didTransaction();

    bool canUse(const Register& reg);
    Register& chooseRegister();
    Register& chooseRegister(const RegisterData& data);
    Register& chooseRegisterFromBack();
    int resolveForbiddenRegister(Register& reg);

    int put(Register& reg, const RegisterData& data);
    Register& has(const RegisterData& data);

private:
    int m_opId { 0 };
    bool m_inTransaction { false };
    std::vector<Transaction> m_transactions;
    CodeGeneratorAarch32& m_codeGenerator;
};

}