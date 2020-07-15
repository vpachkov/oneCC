#pragma once
#include "../../AST/AbstractAST.h"
#include "../../AST/ASTNode.h"
#include "Token.h"
#include <cstdint>
#include <iostream>
#include <string>
#include <map>
#include <stack>

namespace oneCC::SemanticAnalyzer {

class Scoper {
public:
    Scoper() = default;
    bool addNode(AST::IdentifierNode* node);
    bool addNode(AST::IdentifierNode* node, int shift);
    void enterScope();
    void exitScope();
    bool checkScope(AST::IdentifierNode* node, int shift=0);
    AST::IdentifierNode* findVar(const std::string& node);

private:
    std::vector<std::pair<AST::IdentifierNode*, int>> m_vars {};
    int m_scopeLevel = 0;
};

}


