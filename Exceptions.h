#pragma once
#include <exception>

namespace oneCC::Exceptions {
class BadArgumentKey : public std::exception {
    virtual const char* what() const throw()
    {
        return "Argument key should start with - or --";
    }
};
class MissingArgument : public std::exception {
    virtual const char* what() const throw()
    {
        return "Missing required argument";
    }
};
}