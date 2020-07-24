#include "ConfigTest.h"
#include "../../Config/Config.h"

namespace oneCC::Tests {

void ConfigTest::test()
{
    auto configInstnaceA = oneCC::Config::Config::get();
    configInstnaceA->testConfigArgument = "test";
    auto configInstnaceB = oneCC::Config::Config::get();
    this->assertEqual(configInstnaceA->testConfigArgument, configInstnaceB->testConfigArgument);
}

}