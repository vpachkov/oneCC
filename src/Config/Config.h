#pragma once
#include <string>

namespace oneCC::Config {
class Config {
public:
    static Config* get()
    {
        if (!m_instance)
            m_instance = new Config();
        return m_instance;
    }
    // args
    std::string filename;
    std::string platform;
    bool version;

    //test arg, please keep your paws away
    std::string testConfigArgument = "";

private:
    static Config* m_instance;
    Config() {}
    Config(const Config&);
    Config& operator=(Config&);
};
}