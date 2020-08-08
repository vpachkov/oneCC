#pragma once

#include "OutputNode.h"
#include <vector>

#ifdef DEBUG_TRANSLATOR_TRACER
#include <experimental/source_location>
#endif

namespace oneCC::CodeGenerator::Aarch32 {

class CodeGeneratorAarch32;

class OutputManager {
public:
    OutputManager(CodeGeneratorAarch32& codeGen);
    int addLabel(const std::string& s);
    int saveSpot();
    int add(const TranslatedOpcode& t);
    int add(TranslatedOpcode&& t);
    int add(int parentNodeId, const TranslatedOpcode& t);
    int add(int parentNodeId, TranslatedOpcode&& t);
    int next(int prevNodeId);
    void setOutputNode(int id) { m_activeOutputNode = id; }
    OutputNode& node(int id) { return m_nodes[id]; }
    OutputNode& activeNode() { return m_nodes[m_activeOutputNode]; }
    OutputNode& rootNode() { return m_nodes[m_rootOutputNode]; }
    void print();

#ifdef DEBUG_TRANSLATOR_TRACER
    int add(const std::experimental::source_location& location, const TranslatedOpcode& t);
    int add(const std::experimental::source_location& location, TranslatedOpcode&& t);
    int add(int parentNodeId, const std::experimental::source_location& location, const TranslatedOpcode& t);
    int add(int parentNodeId, const std::experimental::source_location& location, TranslatedOpcode&& t);
#endif
private:
    void visit(int nodeId);

    const int m_rootOutputNode { 0 };
    int m_activeOutputNode { 0 };
    CodeGeneratorAarch32& m_codeGenerator;
    std::vector<OutputNode> m_nodes;
};

}