#include "ArgsParserTest.h"
#include <cstring>
#include "../../ArgsParser/ArgsParser.h"
#include "../../Config/Config.h"
#include "../../Exceptions.h"

namespace oneCC::Tests {

int ArgsParserTest::defaultTestArgc = 5;

char** ArgsParserTest::m_buildTestArgv()
{
    std::string argvString[] = { "always filename", "-s", "test", "--argument-long", "example", };
    char** argv = new char*[ArgsParserTest::defaultTestArgc];
    for (int i = 0; i < ArgsParserTest::defaultTestArgc; i++) {
        argv[i] = new char[argvString[i].size() + 1];
        strcpy(argv[i], argvString[i].c_str());
    }
    return argv;
}

void ArgsParserTest::test()
{
    // initializing config, args parser and test data
    auto configInstnace = oneCC::Config::Config::get();
    auto argsParser = new oneCC::ArgsParser::ArgsParser();
    char** argv = m_buildTestArgv();
    int argc = 5;
    argsParser->loadArgs(argc, argv);

    // get argument by short key
    argsParser->registerArgument(configInstnace->testСonfigArgument, "--lol", "-s");
    this->assertEqual(std::string("test"), configInstnace->testСonfigArgument);

     // get argument by long key
    argsParser->registerArgument(configInstnace->testСonfigArgument, "--argument-long", "-g");
    this->assertEqual(std::string("example"), configInstnace->testСonfigArgument);

    // make sure, that exceptions work
    auto registerByWrongKey = [&](){ argsParser->registerArgument(configInstnace->testСonfigArgument, "f", "-g"); };
    this->assertThrows<oneCC::Exceptions::BadArgumentKey>(registerByWrongKey);

    auto registerByUnknownArg = [&](){ argsParser->registerArgument(configInstnace->testСonfigArgument, "--fff", "-g", true); };
    this->assertThrows<oneCC::Exceptions::MissingArgument>(registerByUnknownArg);

}

}