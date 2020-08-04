#include "TransactionManager.h"
#include "../CodeGenerator.h"
#include <cassert>
#include <iostream>

namespace oneCC::CodeGenerator::Aarch32 {

TransactionManager::TransactionManager(CodeGeneratorAarch32& codeGen)
    : m_codeGenerator(codeGen)
{
}

// Creates a new transaction
void TransactionManager::create(bool ignoreForbiddenRegisters)
{
    m_inTransaction = true;
    m_transactions.emplace_back(m_trasnactionId++);

    // Forbid registers which have been forbidden in prev transaction
    if (!ignoreForbiddenRegisters && m_transactions.size() > 1) {
        uint32_t mask = m_transactions[m_transactions.size() - 2].mask();
        m_transactions.back().setWhiteListRegisters(mask);
    }
}

// Returns the last transaction, it's also an active transaction.
Transaction& TransactionManager::active()
{
    // If we don't have an active transaction, we will return a fake one.
    // Writing to it won't would save us from an ub.
    if (!m_inTransaction) [[unlikely]] {
        return Transaction::Fake();
    }
    return m_transactions.back();
}

// Finishes the last transaction.
void TransactionManager::end()
{
    assert(!m_transactions.empty());

    m_transactions.back().restoreReplaces([&](std::pair<Register&, Register&>& replace) {
        // We use this hack to allow the replacement back. We don't think about correctness, since the transaction ends here.
        m_transactions.back().allowRegister(replace.first);
        if (m_codeGenerator.registerManager().replace(replace.first, replace.second.data()) == 0) {
            m_codeGenerator.output().add(m_codeGenerator.translator().MOV_reg(replace.first, replace.second));
        }
    });

    m_transactions.pop_back();
    m_inTransaction = !m_transactions.empty();
}

}