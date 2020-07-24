#pragma once
#include "AbstractTest.h"
#include <iostream>
#include <memory>
#include <queue>
#include <string>

namespace oneCC::Tests {
class Tester {
public:
    Tester() {}
    ~Tester() {}

    template <class T>
    void addTest(std::shared_ptr<T> test)
    {
        m_queue.push_back(std::dynamic_pointer_cast<AbstractTest>(test));
    }

    bool run()
    {
        bool result = true;
        for (auto i : m_queue) {
            i->test();
            bool testResult = i->result();
            Tester::print(testResult, i);
            result &= testResult;
        }
        return result;
    }

private:
    void print(bool res, std::shared_ptr<AbstractTest> test)
    {
        if (!res) {
            std::cout << "\u001b[31mFailed: \u001b[0m" << test->name() << "\n";
            for (std::string& resultDetail : test->resultDetails()) {
                std::cout << "\t" << resultDetail << "\n";
            }
        } else {
            std::cout << "\u001b[32;1mPass: \u001b[0m" << test->name() << "\n";
        }
    }

    std::vector<std::shared_ptr<AbstractTest>> m_queue;
};
}