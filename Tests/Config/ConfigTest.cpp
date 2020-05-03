#include "ConfigTest.h"
#include "../../Config/Config.h"

namespace oneCC::Tests {

void ConfigTest::test()
{
    auto configInstaneA = oneCC::Config::Config::get();
    configInstaneA->testСonfigArgument = "test";
    auto configInstaneB = oneCC::Config::Config::get();
    this->assertEqual(configInstaneA->testСonfigArgument, configInstaneB->testСonfigArgument);
}

}