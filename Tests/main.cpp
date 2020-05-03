#include "Lexer/LexerTest.h"
#include "Config/ConfigTest.h"
#include "Tester.h"

int main()
{
    using namespace oneCC::Tests;
    auto tester = Tester();
    tester.addTest(std::make_shared<LexerTest>());
    tester.addTest(std::make_shared<ConfigTest>());
    if (!tester.run()) {
        return 1;
    }
    return 0;
}