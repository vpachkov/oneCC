#pragma once
#include "AbstractAST.h"
#include "Token.h"
#include <cstdint>
#include <iostream>
#include <string>
#include <map>

namespace oneCC::SemanticAnalyzer {

class FunctionCollector : public AST::AbstractAST {
public:
    FunctionCollector() = default;
    std::map<std::string, AST::Node*> getFunctions(AST::Node* program){
        FunctionCollector::visitNode(program);
        return m_functionMap;
    }
private:
    // From AST::AbstractAST
    using AST::AbstractAST::visitNode;
    void visitNode(AST::FunctionNode* a) override {
        m_functionMap[a->name()] = a;
    }
    void visitNode(AST::ProgramNode* a) override {
        for (auto* arg : a->funcs()) {
            visitNode(arg);
        }
    }

    std::map<std::string, AST::Node*> m_functionMap;
};

}