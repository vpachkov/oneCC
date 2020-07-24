#pragma once
#include <exception>
#include <string>
#include <vector>
#include <functional>

#include "../Utils/Utils.h"

namespace oneCC::Tests {
class AbstractTest {

public:
    AbstractTest() {}
    virtual ~AbstractTest() {}
    virtual std::string name() = 0;
    virtual void test() = 0;
    virtual void clear() = 0;

    bool result() { return m_result; }
    std::vector<std::string>& resultDetails() { return m_resultDetails; }

protected:
    template <typename T>
    bool assertEqual(T valueA, T valueB)
    {
        std::string valueAString = oneCC::Utils::toString(valueA);
        std::string valueBString = oneCC::Utils::toString(valueB);

        bool assertationResult = valueAString == valueBString;
        if (!assertationResult) {
            m_resultDetails.push_back(
                "Assertation faied, " + valueAString + " != " + valueBString);
        }
        m_result &= (assertationResult);
        return assertationResult;
    }

    bool assertTrue(bool value)
    {
        if (!value) {
            m_resultDetails.push_back("Assertation failed, " + oneCC::Utils::toString(value));
        }
        m_result &= value;
        return value;
    }

    bool assertFalse(bool value)
    {
        return assertTrue(!value);
    }

    template <typename T>
    bool assertThrows(const std::function<void()>& func)
    {
        try {
            func();
        } catch (T& e) {
            return true;
        } catch (...) {
            m_resultDetails.push_back("Assertation failed, function throwed unknown exception");
        }
        m_resultDetails.push_back("Assertation failed, function throwed nothing");
        m_result = false;
        return false;
    }

private:
    std::vector<std::string> m_resultDetails;
    bool m_result = true;
};
}