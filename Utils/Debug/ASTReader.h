#pragma once
#include "../../AST/ASTNode.h"
#include "../../AST/Nodes/BinaryOperation.h"
#include "../../AST/Nodes/IntConst.h"
#include "../../Lexer/Token.h"
#include <cstdint>
#include <iostream>
#include <string>

namespace oneCC::ASTUtils {

class Visualizer {
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

    int visitNode(AST::Node* a);
    int visitNode(AST::BinaryOperationNode* a);
    int visitNode(AST::IntConstNode* a);

    std::string toText(AST::BinaryOperationNode*);
    std::string toText(AST::IntConstNode*);

    int m_tin;
    std::vector<std::vector<int>> m_children;
    std::vector<std::string> m_labels;
    std::string m_saveTo;
};
}