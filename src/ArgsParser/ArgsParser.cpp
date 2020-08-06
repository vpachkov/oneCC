#include "ArgsParser.h"
#include "../Exceptions.h"
#include "../Utils/Utils.h"

namespace oneCC::ArgsParser {

ArgsParser::ArgsParser()
{
}
ArgsParser::ArgsParser(int argc, char* argv[])
{
    loadArgs(argc, argv);
}
void ArgsParser::loadArgs(int argc, char* argv[])
{
    for (size_t i = 1; i < argc; i++) {
        m_arguments.push_back(argv[i]);
    }
}
void ArgsParser::registerArgument(std::string& configField, std::string argumentLong,
    std::string argumentShort, bool required)
{
    if (m_arguments.empty())
        return;
        
    m_validateArgumentKeys(argumentLong, argumentShort);

    for (size_t i = 0; i < m_arguments.size() - 1; i++) {
        const std::string& argumentKey = m_arguments[i];
        if (argumentKey == argumentLong || (argumentShort != NULL_ARGUMENT && argumentKey == argumentShort)) {
            configField = m_arguments[i + 1];
            return;
        }
    }
    if (required) {
        throw oneCC::Exceptions::MissingArgument();
    }
}
void ArgsParser::registerArgument(int& configField, std::string argumentLong,
    std::string argumentShort, bool required)
{
    if (m_arguments.empty())
        return;

    m_validateArgumentKeys(argumentLong, argumentShort);

    for (size_t i = 0; i < m_arguments.size() - 1; i++) {
        const std::string& argumentKey = m_arguments[i];
        if (argumentKey == argumentLong || (argumentShort != NULL_ARGUMENT && argumentKey == argumentShort)) {
            configField = std::stoi(m_arguments[i + 1]);
            return;
        }
    }
    if (required) {
        throw oneCC::Exceptions::MissingArgument();
    }
}
void ArgsParser::registerArgument(bool& configField, std::string argumentLong,
    std::string argumentShort)
{
    m_validateArgumentKeys(argumentLong, argumentShort);

    for (size_t i = 0; i < m_arguments.size(); i++) {
        const std::string& argumentKey = m_arguments[i];
        if (argumentKey == argumentLong || (argumentShort != NULL_ARGUMENT && argumentKey == argumentShort)) {
            configField = true;
            return;
        }
    }

    configField = false;
}
void ArgsParser::m_validateArgumentKeys(std::string& argumentLong, std::string& argumentShort)
{
    if (argumentLong.size() <= 2 || argumentLong[0] != '-' || argumentLong[1] != '-') {
        throw oneCC::Exceptions::BadArgumentKey();
    }
    if (argumentShort != NULL_ARGUMENT) {
        if (argumentShort.size() <= 1 || argumentShort[0] != '-') {
            throw oneCC::Exceptions::BadArgumentKey();
        }
    }
}
};