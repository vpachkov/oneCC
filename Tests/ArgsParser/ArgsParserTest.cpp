#include "ArgsParserTest.h"
#include "../../ArgsParser/ArgsParser.h"
#include "../../Config/Config.h"
#include "../../Exceptions.h"
#include <cstring>

namespace oneCC::Tests {

int ArgsParserTest::defaultTestArgc = 5;

char** ArgsParserTest::m_buildTestArgv()
{
    std::string argvString[] = {
        "always filename",
        "-s",
        "test",
        "--argument-long",
        "example",
    };
    char** argv = new char*[ArgsParserTest::defaultTestArgc];
    for (int i = 0; i < ArgsParserTest::defaultTestArgc; i++) {
        argv[i] = new char[argvString[i].size() + 1];
        strcpy(argv[i], argvString[i].c_str());
    }
    return argv;
}

void ArgsParserTest::test()
{
    // Initializing config, args parser and test data.
    auto configInstnace = oneCC::Config::Config::get();
    auto argsParser = new oneCC::ArgsParser::ArgsParser();
    char** argv = m_buildTestArgv();
    int argc = 5;
    argsParser->loadArgs(argc, argv);

    // Get argument by short key.
    argsParser->registerArgument(configInstnace->testConfigArgument, "--lol", "-s");
    this->assertEqual(std::string("test"), configInstnace->testConfigArgument);

    // Get argument by long key.
    argsParser->registerArgument(configInstnace->testConfigArgument, "--argument-long", "-g");
    this->assertEqual(std::string("example"), configInstnace->testConfigArgument);

    // Make sure that exceptions work.
    auto registerByWrongKey = [&]() { argsParser->registerArgument(configInstnace->testConfigArgument, "f", "-g"); };
    this->assertThrows<oneCC::Exceptions::BadArgumentKey>(registerByWrongKey);

    auto registerByUnknownArg = [&]() { argsParser->registerArgument(configInstnace->testConfigArgument, "--fff", "-g", true); };
    this->assertThrows<oneCC::Exceptions::MissingArgument>(registerByUnknownArg);
}

}