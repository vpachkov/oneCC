#pragma once

#include "../Common/Regs.h"
#include "Transaction.h"
#include <vector>

namespace oneCC::CodeGenerator::Aarch32 {

class RegisterManager {
public:
    RegisterManager() = default;

    void initiateTransaction(bool ignoreForbiddenRegisters = false);
    Transaction& activeTransaction();
    void didTransaction();

    Register& chooseRegister();
    Register& chooseRegister(const RegisterData& data);

    int save(Register& reg, const RegisterData& data);
    Register& has(const RegisterData& data);

private:
    int m_opId { 0 };
    bool m_inTransaction { false };
    std::vector<Transaction> m_transactions;
    
};

}