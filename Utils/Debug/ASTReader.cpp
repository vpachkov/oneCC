#include "ASTReader.h"
#include <cassert>
#include <fstream>
#include <string>
#include <time.h>

namespace oneCC::ASTUtils {

char Visualizer::tokenTypeToString(int tokenType)
{
    switch (tokenType) {
    case Lexer::TokenType::Plus:
        return '+';
    case Lexer::TokenType::Minus:
        return '-';
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
    case Lexer::TokenType::TypeInt:
        return 'i';
    case Lexer::TokenType::TypeFloat:
        return 'f';
    default:
        return '?';
    }
}

void Visualizer::genDotDescriptor(AST::Node* node, std::string filename)
{
    startVisitingTree(node);

    assert(m_tin != -1);
    assert(m_level == 0);

    std::ofstream file;
    file.open(filename);
    file << "digraph AST {\n";
    file << "node [shape=box];\n";
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

void Visualizer::pushTin(int tin)
{
    m_childrenStack.push_back(std::make_pair(m_level, tin));
}

std::vector<int> Visualizer::popChildrenTins()
{
    std::vector<int> res;
    while (!m_childrenStack.empty()) {
        if (m_childrenStack.back().first == m_level + 1) {
            res.push_back(m_childrenStack.back().second);
            m_childrenStack.pop_back();
        } else {
            break;
        }
    }
    return res;
}

// Warning: If you want ot create a reader of new node, please, use the same
// structure as used in existed visitNode, overwise this could break the whole
// reader, since it works on stack, and if won't push or pop, you can get the
// wrong result.
void Visualizer::startVisitingTree(AST::Node* node)
{
    m_tin = -1;
    m_level = 0;
    m_labels.clear();
    m_children.clear();

    visitNode(node);
}

void Visualizer::visitNode(AST::BinaryOperationNode* node)
{
    increaseLevel();
    int myTin = tin();

    visitNode(node->leftChild());
    visitNode(node->rightChild());

    m_labels[myTin] = toText(node);
    m_children[myTin] = popChildrenTins();

    pushTin(myTin);
    decreaseLevel();
}

std::string Visualizer::toText(AST::BinaryOperationNode* node)
{
    std::string res;
    res += Visualizer::tokenTypeToString(node->operation());
    return res;
}

void Visualizer::visitNode(AST::TernaryOperationNode* node)
{
    increaseLevel();
    int myTin = tin();

    visitNode(node->leftChild());
    visitNode(node->middleChild());
    visitNode(node->rightChild());

    m_labels[myTin] = toText(node);
    m_children[myTin] = popChildrenTins();

    pushTin(myTin);
    decreaseLevel();
}

std::string Visualizer::toText(AST::TernaryOperationNode* node)
{
    std::string res("tOp");
    return res;
}

void Visualizer::visitNode(AST::TypeNode* node)
{
    increaseLevel();
    int myTin = tin();

    m_labels[myTin] = toText(node);
    m_children[myTin] = popChildrenTins();

    pushTin(myTin);
    decreaseLevel();
}

std::string Visualizer::toText(AST::TypeNode* node)
{
    std::string res;
    res += Visualizer::tokenTypeToString(node->type());
    return res;
}

void Visualizer::visitNode(AST::IdentifierNode* node)
{
    increaseLevel();
    int myTin = tin();

    m_labels[myTin] = toText(node);
    m_children[myTin] = popChildrenTins();

    pushTin(myTin);
    decreaseLevel();
}

std::string Visualizer::toText(AST::IdentifierNode* node)
{
    std::string res("Var ");
    res += node->value();
    return res;
}

void Visualizer::visitNode(AST::BlockStatementNode* node)
{
    increaseLevel();
    int myTin = tin();

    for (auto* statment : node->statements()) {
        visitNode(statment);
    }

    m_labels[myTin] = toText(node);
    m_children[myTin] = popChildrenTins();

    pushTin(myTin);
    decreaseLevel();
}

std::string Visualizer::toText(AST::BlockStatementNode* node)
{
    std::string res("Block");
    return res;
}

void Visualizer::visitNode(AST::ReturnStatementNode* node)
{
    increaseLevel();
    int myTin = tin();

    visitNode(node->returnedExpression());

    m_labels[myTin] = toText(node);
    m_children[myTin] = popChildrenTins();

    pushTin(myTin);
    decreaseLevel();
}

std::string Visualizer::toText(AST::ReturnStatementNode* node)
{
    std::string res("ret");
    return res;
}

void Visualizer::visitNode(AST::FunctionNode* node)
{
    increaseLevel();
    int myTin = tin();

    visitNode(node->statement());
    for (auto* arg : node->arguments()) {
        visitNode(arg);
    }

    m_labels[myTin] = toText(node);
    m_children[myTin] = popChildrenTins();

    pushTin(myTin);
    decreaseLevel();
}

std::string Visualizer::toText(AST::FunctionNode* node)
{
    std::string res;
    res += Visualizer::tokenTypeToString(node->type());
    res += " ";
    res += node->name();
    return res;
}

void Visualizer::visitNode(AST::FunctionArgumentNode* node)
{
    increaseLevel();
    int myTin = tin();

    m_labels[myTin] = toText(node);
    m_children[myTin] = popChildrenTins();

    pushTin(myTin);
    decreaseLevel();
}

std::string Visualizer::toText(AST::FunctionArgumentNode* node)
{
    std::string res;
    res += Visualizer::tokenTypeToString(node->type());
    res += ' ';
    res += node->name();
    return res;
}

void Visualizer::visitNode(AST::FunctionCallNode* node)
{
    increaseLevel();
    int myTin = tin();

    for (auto* arg : node->arguments()) {
        visitNode(arg);
    }

    m_labels[myTin] = toText(node);
    m_children[myTin] = popChildrenTins();

    pushTin(myTin);
    decreaseLevel();
}

std::string Visualizer::toText(AST::FunctionCallNode* node)
{
    std::string res("call ");
    res += node->name();
    return res;
}

void Visualizer::visitNode(AST::ProgramNode* node)
{
    increaseLevel();
    int myTin = tin();

    for (auto* arg : node->nodes()) {
        visitNode(arg);
    }

    m_labels[myTin] = toText(node);
    m_children[myTin] = popChildrenTins();

    pushTin(myTin);
    decreaseLevel();
}

std::string Visualizer::toText(AST::ProgramNode* node)
{
    std::string res("prog");
    return res;
}

void Visualizer::visitNode(AST::IntConstNode* node)
{
    increaseLevel();
    int myTin = tin();

    m_labels[myTin] = toText(node);
    m_children[myTin] = popChildrenTins();

    pushTin(myTin);
    decreaseLevel();
}

std::string Visualizer::toText(AST::IntConstNode* node)
{
    std::string res(std::to_string(node->value()));
    return res;
}

}