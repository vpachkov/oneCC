#include "Scoper.h"

namespace oneCC::SemanticAnalyzer{

void Scoper::enterScope() {
    m_scopeLevel++;
}

void Scoper::exitScope() {
    while(!m_vars.empty() && m_vars.back().second == m_scopeLevel) {
        m_vars.pop_back();
    }
    m_scopeLevel--;
}

bool Scoper::addNode(AST::IdentifierNode* node) {
    if (checkScope(node)) {
        m_vars.emplace_back(node, m_scopeLevel);
        return true;
    }
    return false;
}

bool Scoper::addNode(AST::IdentifierNode *node, int shift) {
    if (checkScope(node)) {
        m_vars.emplace_back(node, m_scopeLevel + shift);
        return true;
    }
    return false;
}

bool Scoper::checkScope(AST::IdentifierNode* node, int shift) {
    auto var = m_vars.rbegin();
    for (; var != m_vars.rend() && (*var).second == m_scopeLevel + shift && (*var).first->value() != node->value() ; var++);
    return var == m_vars.rend() || (*var).first->value() != node->value();
}

AST::IdentifierNode* Scoper::findVar(const std::string& node) {
    auto var = m_vars.rbegin();
    for (; var != m_vars.rend() && (*var).first->value() != node; var++ );
    return var == m_vars.rend() ? NULL : (*var).first;
}

}
