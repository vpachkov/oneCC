#include "Lexer/LexerTest.h"
#include "Tester.h"

int main()
{
    using namespace oneCC::Tests;
    auto tester = Tester();
    tester.addTest(std::make_shared<LexerTest>());
    if (!tester.run()) {
        return 1;
    }
    return 0;
}