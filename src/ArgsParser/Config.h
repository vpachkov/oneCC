#pragma once
#include <string>

#ifndef CONFIG_STANDARD_TARGET_PLATFROM
#define CONFIG_STANDARD_TARGET_PLATFROM "X86_32"
#endif

namespace oneCC::ArgsParser {
class Config {
public:
    static Config& the()
    {
        static Config conf;
        return conf;
    }
    
    // Args
    std::string filename;
    std::string platform { CONFIG_STANDARD_TARGET_PLATFROM };

#ifdef TESTING
    std::string testConfigArgument {};
#endif
private:
    Config() {}
    Config(const Config&);
    Config& operator=(Config&);
};
}