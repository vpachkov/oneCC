#pragma once
#include <memory>
#include <string>

namespace oneCC::Config {
    class Config {
    private:
        static Config* m_instance;
        Config() {}
        Config(const Config&);
        Config& operator=(Config&);

    public:
        static Config* get()
        {
            if (!m_instance)
                m_instance = new Config();
            return m_instance;
        }
        // args
        std::string filename;
    };
}
