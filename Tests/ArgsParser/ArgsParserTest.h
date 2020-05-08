#pragma once
#include "../AbstractTest.h"

namespace oneCC::Tests {
class ArgsParserTest : public AbstractTest {
public:
    std::string name() override { return "ArgsParserTest"; }
    void test() override;
    void clear() override {}
    ~ArgsParserTest() {}

private:
    char** m_buildTestArgv();
    static int defaultTestArgc;
};
}