#pragma once
#include "Config.h"
#include <string>
#include <vector>

#define NULL_ARGUMENT ""

namespace oneCC::ArgsParser {

enum ArgFieldType {
    Bool,
    Int,
    String,
};

class ArgData {
public:
    ArgData() {}

    ArgData(void* df, ArgFieldType dt, const std::string& argShort, const std::string& argLong, bool req = false)
        : m_dataField(df)
        , m_dataType(dt)
        , m_argShort(argShort)
        , m_argLong(argLong)
        , m_req(req)
    {
    }

    std::string& argShort() { return m_argShort; }
    std::string& argLong() { return m_argLong; }
    ArgFieldType argType() { return m_dataType; }
    void* holder() { return m_dataField; }

private:
    std::string m_argShort;
    std::string m_argLong;
    void* m_dataField;
    ArgFieldType m_dataType;
    bool m_req;
};

}