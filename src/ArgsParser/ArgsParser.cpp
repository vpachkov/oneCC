#include "ArgsParser.h"
#include "../Exceptions.h"
#include "../Utils/Utils.h"
#include <cassert>
#include <iostream>

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

void ArgsParser::process()
{
    for (ArgData& adata : m_eaters) {
        for (int i = 0; i < (int)m_arguments.size() - 1; i++) {
            const std::string& argumentKey = m_arguments[i];
            if (argumentKey == adata.argLong() || argumentKey == adata.argShort()) {
                if (adata.argType() == ArgFieldType::Int) {
                    *((int*)adata.holder()) = std::stoi(m_arguments[i + 1]);
                } else if (adata.argType() == ArgFieldType::String) {
                    *((std::string*)adata.holder()) = m_arguments[i + 1];
                } else if (adata.argType() == ArgFieldType::Bool) {
                    *((bool*)adata.holder()) = true;
                }
            }
        }
    }
}

void ArgsParser::registerArgument(std::string* configField, const std::string& argumentLong, const std::string& argumentShort, bool required)
{
    assert(validateArgumentKeys(argumentLong, argumentShort));
    m_eaters.emplace_back(configField, ArgFieldType::String, argumentShort, argumentLong, required);
}

void ArgsParser::registerArgument(int* configField, const std::string& argumentLong, const std::string& argumentShort, bool required)
{
    assert(validateArgumentKeys(argumentLong, argumentShort));
    m_eaters.emplace_back(configField, ArgFieldType::Int, argumentShort, argumentLong, required);
}

void ArgsParser::registerArgument(bool* configField, const std::string& argumentLong, const std::string& argumentShort)
{
    assert(validateArgumentKeys(argumentLong, argumentShort));
    m_eaters.emplace_back(configField, ArgFieldType::Bool, argumentShort, argumentLong);
    *configField = false;
}

bool ArgsParser::validateArgumentKeys(const std::string& argumentLong, const std::string& argumentShort) const
{
    if (argumentLong.size() <= 2 || argumentLong[0] != '-' || argumentLong[1] != '-') {
        return false;
    }

    if (argumentShort != NULL_ARGUMENT) {
        if (argumentShort.size() <= 1 || argumentShort[0] != '-') {
            return false;
        }
    }

    return true;
}
};