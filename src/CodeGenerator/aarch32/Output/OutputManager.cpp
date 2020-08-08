#include "OutputManager.h"
#include "../CodeGenerator.h"

namespace oneCC::CodeGenerator::Aarch32 {

OutputManager::OutputManager(CodeGeneratorAarch32& codeGen)
    : m_codeGenerator(codeGen)
{
    m_nodes.push_back(OutputNode(true));
    m_activeOutputNode = 0;
}

int OutputManager::addLabel(const std::string& s)
{
    m_nodes.push_back(OutputNode(true));
    m_nodes.back().setOpcode(TranslatedOpcode(std::string(s + ":")));
    activeNode().addChild(m_nodes.size() - 1);
    return m_nodes.size() - 1;
}

int OutputManager::add(const TranslatedOpcode& t)
{
    m_nodes.push_back(OutputNode(t));
    activeNode().addChild(m_nodes.size() - 1);
    return m_nodes.size() - 1;
}

int OutputManager::add(TranslatedOpcode&& t)
{
    m_nodes.push_back(OutputNode(std::move(t)));
    activeNode().addChild(m_nodes.size() - 1);
    return m_nodes.size() - 1;
}

int OutputManager::add(int patrentNodeId, const TranslatedOpcode& t)
{
    m_nodes.push_back(OutputNode(t));
    m_nodes[patrentNodeId].addChild(m_nodes.size() - 1);
    return m_nodes.size() - 1;
}

int OutputManager::add(int patrentNodeId, TranslatedOpcode&& t)
{
    m_nodes.push_back(OutputNode(std::move(t)));
    m_nodes[patrentNodeId].addChild(m_nodes.size() - 1);
    return m_nodes.size() - 1;
}

#ifdef DEBUG_TRANSLATOR_TRACER
int OutputManager::add(const std::experimental::source_location& location, const TranslatedOpcode& t)
{
    m_nodes.push_back(OutputNode(t));
    activeNode().addChild(m_nodes.size() - 1);
    m_nodes.back().setLocation(location);
    return m_nodes.size() - 1;
}

int OutputManager::add(const std::experimental::source_location& location, TranslatedOpcode&& t)
{
    m_nodes.push_back(OutputNode(std::move(t)));
    activeNode().addChild(m_nodes.size() - 1);
    m_nodes.back().setLocation(location);
    return m_nodes.size() - 1;
}

int OutputManager::add(int patrentNodeId, const std::experimental::source_location& location, const TranslatedOpcode& t)
{
    m_nodes.push_back(OutputNode(t));
    m_nodes[patrentNodeId].addChild(m_nodes.size() - 1);
    m_nodes.back().setLocation(location);
    return m_nodes.size() - 1;
}

int OutputManager::add(int patrentNodeId, const std::experimental::source_location& location, TranslatedOpcode&& t)
{
    m_nodes.push_back(OutputNode(std::move(t)));
    m_nodes[patrentNodeId].addChild(m_nodes.size() - 1);
    m_nodes.back().setLocation(location);
    return m_nodes.size() - 1;
}
#endif

// FIXME: May not work with labels
int OutputManager::next(int prevNodeId)
{
    return prevNodeId + 1;
}

void OutputManager::print()
{
    visit(m_rootOutputNode);
}

void OutputManager::visit(int nodeId)
{
    m_nodes[nodeId].print();
    m_nodes[nodeId].foreachChild([&](int childNodeId) {
        if (m_nodes[childNodeId].isLabel()) {
            visit(childNodeId);
        } else {
            m_nodes[childNodeId].print();
        }
    });
}

}