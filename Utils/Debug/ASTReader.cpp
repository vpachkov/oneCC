#include "ASTReader.h"
#include <fstream>
#include <string>
#include <time.h>

namespace oneCC::ASTUtils {

char Visualizer::tokenTypeToString(int tokenType)
{
    switch (tokenType) {
    case Lexer::TokenType::Plus:
        return '+';
    case Lexer::TokenType::Multiply:
        return '*';
    case Lexer::TokenType::Divide:
        return '/';
    case Lexer::TokenType::Assign:
        return '=';
    case Lexer::TokenType::OpenRoundBracket:
        return '(';
    case Lexer::TokenType::CloseRoundBracket:
        return ')';
    default:
        return '?';
    }
}

void Visualizer::genDotDescriptor(AST::Node* node, std::string filename)
{
    startVisitingTree(node);

    std::ofstream file;
    file.open(filename);
    file << "digraph AST {\n";
    file << "node [shape=box];\n";
    std::cout << m_tin << " kek\n";
    for (int i = 0; i <= m_tin; i++) {
        file << std::to_string(i) << " [label=\"" << m_labels[i] << "\"];\n";
    }
    for (int i = 0; i <= m_tin; i++) {
        for (int childId : m_children[i]) {
            file << std::to_string(i) << " -> " << std::to_string(childId) << "\n";
        }
    }
    file << "}\n";
    file.close();
}

void Visualizer::genTreePng(AST::Node* node)
{

    time_t seconds;
    seconds = time(NULL);

    std::string resultFilename(m_saveTo + std::to_string(seconds) + ".png");
    std::string srcFilename(m_saveTo + std::to_string(seconds) + ".dot");

    // TODO: Rewrite in normal way.
    std::string mkdircmd("mkdir -p " + m_saveTo);
    system(mkdircmd.c_str());

    genDotDescriptor(node, srcFilename);

    std::string cmd("dot -Tpng " + srcFilename + " -o " + resultFilename);
    system(cmd.c_str());

    m_labels.clear();
    m_children.clear();
}

// Node to text

void Visualizer::startVisitingTree(AST::Node* node)
{
    m_tin = -1;
    m_labels.clear();
    m_children.clear();

    visitNode(node);
}

// It tries to convert the node into diverted type, if it's possible and leave the function.
#define tryConvertTo(x, y)                                                                          \
    if (node->type() == y) {                                                                        \
        auto* ptr = dynamic_cast<x*>(node);                                                         \
        if (ptr) {                                                                                  \
            return visitNode(ptr);                                                                  \
        }                                                                                           \
        std::cout << "\nError: dynamic_cast can't convert, but type shows that it's possible!!!\n"; \
    }

// Do NOT change @node param name since it's used in define (which is upper).
int Visualizer::visitNode(AST::Node* node)
{
    // TODO: Work on define, too many params now.
    tryConvertTo(AST::IntConstNode, AST::NodeType::Const);
    tryConvertTo(AST::BinaryOperationNode, AST::NodeType::BinaryOperation);
    return -1; // Means no translation for a node found.
}

int Visualizer::visitNode(AST::BinaryOperationNode* node)
{
    int myTin = ++m_tin;

    m_labels.push_back(toText(node));
    m_children.push_back(std::vector<int>());

    int leftTin = visitNode(node->leftChild());
    int rightTin = visitNode(node->rightChild());

    m_children[myTin].push_back(leftTin);
    m_children[myTin].push_back(rightTin);

    return myTin;
}

std::string Visualizer::toText(AST::BinaryOperationNode* node)
{
    std::string res;
    res += Visualizer::tokenTypeToString(node->operation());
    return res;
}

int Visualizer::visitNode(AST::IntConstNode* node)
{
    int myTin = ++m_tin;

    m_labels.push_back(toText(node));
    m_children.push_back(std::vector<int>());

    return myTin;
}

std::string Visualizer::toText(AST::IntConstNode* node)
{
    std::string res(std::to_string(node->value()));
    return res;
}

}