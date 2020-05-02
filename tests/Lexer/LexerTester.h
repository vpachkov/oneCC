#pragma once
#include "../Tester.h"

namespace oneCC::Tests {
    class LexerTester : public Tester {
    public:
        std::string name() override { return "Lexer Test"; }
        bool test() override;
        void clear() override { } 
        ~LexerTester() { }

    private:
        bool compareFiles(const std::string& filename1, const std::string& filename2);
    };
}