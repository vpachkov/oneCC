#pragma once
#include <queue>
#include <string>

namespace oneCC::Tests {
    class Tester {
    public:
        Tester() { }
        virtual ~Tester() { };
        virtual std::string name() = 0;
        virtual bool test() = 0;
        virtual void clear() = 0;
    };
}