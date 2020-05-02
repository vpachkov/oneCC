#pragma once
#include <string>

namespace oneCC::Tests {
class AbstractTest {
public:
    AbstractTest() {}
    virtual ~AbstractTest() {}
    virtual std::string name() = 0;
    virtual bool test() = 0;
    virtual void clear() = 0;
};
}