#include "Tester.h"
#include "Lexer/LexerTester.h"
#include <iostream>
#include <queue>
#include <memory>

using namespace oneCC::Tests;

std::vector<Tester*> queue;

template<class T> 
void addTest(T* test) {
    queue.push_back(dynamic_cast<Tester*>(test));
}

void addTesters() {
    addTest(new LexerTester());
}

bool run() {
    bool result = true;
    for (auto i : queue) {
        bool testRes = i->test();
        if (!testRes) {
            std::cout << "\u001b[31mError: \u001b[0m" << i->name();
        } else {
            std::cout << "\u001b[32;1mPass: \u001b[0m" << i->name();
        }
        std::cout << "\n";
        result &= testRes;
    }
    return result;
}

int main() {
    addTesters();
    assert(run());
    return 0;
}