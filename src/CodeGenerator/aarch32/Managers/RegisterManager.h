#pragma once

#include "../Common/Regs.h"
#include "Transaction.h"
#include <vector>

namespace oneCC::CodeGenerator::Aarch32 {

class RegisterManager {
public:
    RegisterManager() = default;

    Transaction& initiateTransaction(bool ignoreForbiddenRegisters = false);
    Transaction& activeTransaction();
    void didTransaction(Transaction&);

    Register& chooseRegister();

private:
    int m_opId { 0 };
    bool m_inTransaction { false };
    std::vector<Transaction> m_transactions;
    
};

}