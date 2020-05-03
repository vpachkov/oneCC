#include "ConfigTest.h"
#include "../../Config/Config.h"

namespace oneCC::Tests {

void ConfigTest::test()
{
    auto config_instane_a = oneCC::Config::Config::get();
    config_instane_a->testСonfigArgument = "test";
    auto config_instance_b = oneCC::Config::Config::get();
    this->assertEqual(config_instane_a->testСonfigArgument, config_instance_b->testСonfigArgument);
}

}