#pragma once
#include "ArgData.h"
#include "Config.h"
#include <string>
#include <vector>

#define NULL_ARGUMENT ""

namespace oneCC::ArgsParser {
class ArgsParser {
public:
    ArgsParser();
    ArgsParser(int argc, char* argv[]);

    void registerArgument(std::string* configField, const std::string& argumentLong, const std::string& argumentShort = NULL_ARGUMENT, bool required = false);
    void registerArgument(int* configField, const std::string& argumentLong, const std::string& argumentShort = NULL_ARGUMENT, bool required = false);
    void registerArgument(bool* configField, const std::string& argumentLong, const std::string& argumentShort = NULL_ARGUMENT);

    void loadArgs(int argc, char* argv[]);
    void process();

    static ArgsParser& the()
    {
        static ArgsParser d;
        d.registerArgument(&Config::the().filename, "--file", "-f");
        d.registerArgument(&Config::the().platform, "--platform", "-p");
        return d;
    }

private:
    std::vector<std::string> m_arguments;
    std::vector<ArgData> m_eaters;
    bool validateArgumentKeys(const std::string& argumentLong, const std::string& argumentShort) const;
};
}