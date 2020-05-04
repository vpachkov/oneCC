#pragma once
#include <string>
#include <vector>

#define NULL_ARGUMENT ""

namespace oneCC::ArgsParser {
class ArgsParser {
public:
    ArgsParser() {};
    ArgsParser(int argc, char* argv[]) {};

    void registerArgument(std::string& configField, std::string argumentLong,
        std::string argumentShort = NULL_ARGUMENT, bool required = false) {};
    void registerArgument(int& configField, std::string argumentLong,
        std::string argumentShort = NULL_ARGUMENT, bool required = false) {};
    void registerArgument(bool& configField, std::string argumentLong,
        std::string argumentShort = NULL_ARGUMENT) {};

    void loadArgs(int argc, char* argv[]) {};

private:
    std::vector<std::string> m_arguments;
    void m_validateArgumentKeys(std::string& argumentLong, std::string& argumentShort) {}
    void m_validateArgumenValue(std::string& argumentValue) {}
};
}