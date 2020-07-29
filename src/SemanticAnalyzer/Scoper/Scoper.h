#pragma once
#include "../../AST/ASTNode.h"
#include "../../AST/AbstractAST.h"
#include <cstdint>
#include <iostream>
#include <map>
#include <stack>
#include <string>

namespace oneCC::SemanticAnalyzer {

class Variable {
public:
    AST::IdentifierNode* identifier {};
    int scopeLevel {0};
    int memoryPosition {0}; // keeps position relative to base pointer
};

class Scoper {
public:
    Scoper() = default;
    bool addNode(AST::IdentifierNode* node);
    bool addNode(AST::IdentifierNode* node, int shift);
    void enterScope();
    void exitScope();
    bool checkScope(AST::IdentifierNode* node, int shift = 0);

    bool setMemoryPosition(AST::IdentifierNode* node, int memoryPosition);
    bool setMemoryPosition(std::string& node, int memoryPosition);

    int getMemoryPosition(AST::IdentifierNode* node);

    AST::IdentifierNode* findVar(const std::string& node);

private:
    std::vector<Variable> m_vars {};
    int m_scopeLevel { 0 };
};

}
