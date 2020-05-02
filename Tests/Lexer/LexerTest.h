#pragma once
#include "../AbstractTest.h"

namespace oneCC::Tests {
class LexerTest : public AbstractTest {
public:
    std::string name() override { return "Lexer Test"; }
    bool test() override;
    void clear() override {}
    ~LexerTest() {}

private:
    bool compareFiles(const std::string& filename1, const std::string& filename2);
};
}