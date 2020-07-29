#include "Scoper.h"

namespace oneCC::SemanticAnalyzer{

void Scoper::enterScope() {
    m_scopeLevel++;
}

void Scoper::exitScope() {
    while(!m_vars.empty() && m_vars.back().scopeLevel == m_scopeLevel) {
        m_vars.pop_back();
    }
    m_scopeLevel--;
}

bool Scoper::addNode(AST::IdentifierNode* node) {
    if (checkScope(node)) {
        m_vars.push_back(Variable{ node, m_scopeLevel });
        return true;
    }
    return false;
}

bool Scoper::addNode(AST::IdentifierNode* node, int shift) {
    if (checkScope(node)) {
        m_vars.push_back(Variable{ node, m_scopeLevel + shift });
        return true;
    }
    return false;
}

bool Scoper::checkScope(AST::IdentifierNode* node, int shift) {
    auto var = m_vars.rbegin();
    for (; var != m_vars.rend() && (*var).scopeLevel == m_scopeLevel + shift && (*var).identifier->value() != node->value() ; var++);
    return var == m_vars.rend() || (*var).identifier->value() != node->value();
}

AST::IdentifierNode* Scoper::findVar(const std::string& node) {
    auto var = m_vars.rbegin();
    for (; var != m_vars.rend() && (*var).identifier->value() != node; var++ );
    return var == m_vars.rend() ? NULL : (*var).identifier;
}

    bool Scoper::setMemoryPosition(AST::IdentifierNode* node, int memoryPosition) {
        auto var = m_vars.rbegin();
        for (; var != m_vars.rend() && (*var).identifier->value() != node->value(); var++ );
        if (var == m_vars.rend()) {
            return false;
        }
        (*var).memoryPosition = memoryPosition;
        return true;
    }

    bool Scoper::setMemoryPosition(std::string &node, int memoryPosition) {
        auto var = m_vars.rbegin();
        for (; var != m_vars.rend() && (*var).identifier->value() != node; var++ );
        if (var == m_vars.rend()) {
            return false;
        }
        (*var).memoryPosition = memoryPosition;
        return true;
    }

    int Scoper::getMemoryPosition(AST::IdentifierNode* node) {
        auto var = m_vars.rbegin();
        for (; var != m_vars.rend() && (*var).identifier->value() != node->value(); var++ );
        if (var == m_vars.rend()) {
            return -1;
        }
        return (*var).memoryPosition;
    }

}
