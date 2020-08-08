#include "OutputNode.h"

namespace oneCC::CodeGenerator::Aarch32 {

OutputNode::OutputNode(int id, bool isLabel)
    : m_isLabel(isLabel)
    , m_id(id)
{
}

OutputNode::OutputNode(int id, const TranslatedOpcode& t)
    : m_translatedOpcode(t)
    , m_isLabel(false)
    , m_id(id)
{
}

OutputNode::OutputNode(int id, TranslatedOpcode&& t)
    : m_translatedOpcode(std::move(t))
    , m_isLabel(false)
    , m_id(id)
{
}

void OutputNode::setOpcode(const TranslatedOpcode& t)
{
    m_translatedOpcode = t;
}

void OutputNode::setOpcode(TranslatedOpcode&& t)
{
    m_translatedOpcode = std::move(t);
}

#ifdef DEBUG_TRANSLATOR_TRACER
void OutputNode::setOpcode(const std::experimental::source_location& location, const TranslatedOpcode& t)
{
    m_location = location;
    m_translatedOpcode = t;
}

void OutputNode::setOpcode(const std::experimental::source_location& location, TranslatedOpcode&& t)
{
    m_location = location;
    m_translatedOpcode = std::move(t);
}
#endif

void OutputNode::print()
{
    if (m_visible) {
#ifdef DEBUG_TRANSLATOR_TRACER
        std::cout << m_location.function_name() << ": " << m_location.line() << " >> ";
#endif
        m_translatedOpcode.print();
    }
}

}