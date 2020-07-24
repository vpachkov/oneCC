#pragma once
#include <sstream>
#include <string>
#include "../Lexer/Token.h"

namespace oneCC::Utils {
template <typename T>
std::string toString(T& value)
{
    std::stringstream s;
    s << value;
    return s.str();
}
}