#include "OutputNode.h"

namespace oneCC::CodeGenerator::Aarch32 {

OutputNode::OutputNode(bool is_label)
    : m_isLabel(is_label)
{
}

OutputNode::OutputNode(const TranslatedOpcode& t)
    : m_translatedOpcode(t)
    , m_isLabel(false)
{
}

OutputNode::OutputNode(TranslatedOpcode&& t)
    : m_translatedOpcode(std::move(t))
    , m_isLabel(false)
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
#ifdef DEBUG_TRANSLATOR_TRACER
        std::cout << m_location.function_name() << ": " << m_location.line() << " >> ";
#endif
    m_translatedOpcode.print();
}

}