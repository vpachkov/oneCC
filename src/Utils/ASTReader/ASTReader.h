#pragma once
#include "../../AST/AbstractAST.h"
#include "../../Lexer/Token.h"
#include <cstdint>
#include <iostream>
#include <string>

namespace oneCC::ASTUtils {

class Visualizer final : public AST::AbstractAST {
public:
    Visualizer()
        : m_saveTo("debug/astViz/") {};
    Visualizer(std::string saveTo)
        : m_saveTo(saveTo) {};

    static char tokenTypeToString(int tokenType);
    void genDotDescriptor(AST::Node* node, std::string filename);
    void genTreePng(AST::Node* node);

private:
    void startVisitingTree(AST::Node* node);

    inline void increaseLevel() { m_level++; }
    inline void decreaseLevel() { m_level--; }
    inline int tin()
    {
        m_labels.push_back("not set");
        m_children.push_back(std::vector<int>());
        return ++m_tin;
    }

    void pushTin(int tin);
    std::vector<int> popChildrenTins();

    // From AST::AbstractAST
    using AST::AbstractAST::visitNode;
    void visitNode(AST::BinaryOperationNode* a) override;
    void visitNode(AST::TernaryOperationNode* a) override;
    void visitNode(AST::TypeNode* a) override;
    void visitNode(AST::IdentifierNode* a) override;
    void visitNode(AST::IfStatementNode* a) override;
    void visitNode(AST::BlockStatementNode* a) override;
    void visitNode(AST::ReturnStatementNode* a) override;
    void visitNode(AST::BooleanSnakeNode* a) override;
    void visitNode(AST::FunctionNode* a) override;
    void visitNode(AST::FunctionArgumentNode* a) override;
    void visitNode(AST::FunctionCallNode* a) override;
    void visitNode(AST::ProgramNode* a) override;
    void visitNode(AST::IntConstNode* a) override;

    std::string toText(AST::BinaryOperationNode*);
    std::string toText(AST::TernaryOperationNode*);
    std::string toText(AST::TypeNode*);
    std::string toText(AST::IdentifierNode*);
    std::string toText(AST::IfStatementNode*);
    std::string toText(AST::BlockStatementNode*);
    std::string toText(AST::ReturnStatementNode*);
    std::string toText(AST::BooleanSnakeNode*);
    std::string toText(AST::FunctionNode*);
    std::string toText(AST::FunctionArgumentNode*);
    std::string toText(AST::FunctionCallNode*);
    std::string toText(AST::ProgramNode*);
    std::string toText(AST::IntConstNode*);

    int m_tin { -1 };
    int m_level { 0 };
    std::vector<std::pair<int, int>> m_childrenStack;
    std::vector<std::vector<int>> m_children;
    std::vector<std::string> m_labels;
    std::string m_saveTo;
};
}