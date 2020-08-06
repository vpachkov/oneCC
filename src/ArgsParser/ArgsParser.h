#pragma once
#include <string>
#include <vector>

#define NULL_ARGUMENT ""

namespace oneCC::ArgsParser {
class ArgsParser {
public:
    ArgsParser();
    ArgsParser(int argc, char* argv[]);

    int registerArgument(std::string& configField, std::string argumentLong, std::string argumentShort = NULL_ARGUMENT, bool required = false);
    int registerArgument(int& configField, std::string argumentLong, std::string argumentShort = NULL_ARGUMENT, bool required = false);
    int registerArgument(bool& configField, std::string argumentLong, std::string argumentShort = NULL_ARGUMENT);

    template <typename Callback>
    int registerHandler(std::string& configField, Callback callback, std::string argumentLong, std::string argumentShort = NULL_ARGUMENT, bool required = false)
    {
        int res = registerArgument(configField, argumentLong, argumentShort, required);
        if (!res) {
            callback(configField);
        }
        return res;
    }

    template <typename Callback>
    int registerHandler(int& configField, Callback callback, std::string argumentLong, std::string argumentShort = NULL_ARGUMENT, bool required = false)
    {
        int res = registerArgument(configField, argumentLong, argumentShort, required);
        if (!res) {
            callback(configField);
        }
        return res;
    }

    template <typename Callback>
    int registerHandler(bool& configField, Callback callback, std::string argumentLong, std::string argumentShort = NULL_ARGUMENT)
    {
        int res = registerArgument(configField, argumentLong, argumentShort);
        if (!res) {
            callback();
        }
        return res;
    }

    void loadArgs(int argc, char* argv[]);

private:
    std::vector<std::string> m_arguments;
    void m_validateArgumentKeys(std::string& argumentLong, std::string& argumentShort);
    void m_validateArgumenValue(std::string& argumentValue);
};
}