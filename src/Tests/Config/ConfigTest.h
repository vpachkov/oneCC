#pragma once
#include "../AbstractTest.h"

namespace oneCC::Tests {
class ConfigTest : public AbstractTest {
public:
    std::string name() override { return "Config Test"; }
    void test() override;
    void clear() override {}
    ~ConfigTest() {}
};
}