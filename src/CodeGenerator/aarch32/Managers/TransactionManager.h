#pragma once

#include "../Common/Regs.h"
#include "Transaction.h"
#include <vector>

namespace oneCC::CodeGenerator::Aarch32 {

class CodeGeneratorAarch32;

class TransactionManager {
public:
    TransactionManager(CodeGeneratorAarch32& codeGen);

    void create(bool ignoreForbiddenRegisters = false);
    Transaction& active();
    void end();
    bool in() { return m_inTransaction; }

private:
    int m_trasnactionId { 0 };
    bool m_inTransaction { false };
    std::vector<Transaction> m_transactions;
    CodeGeneratorAarch32& m_codeGenerator;
};

}