#pragma once
#include <exception>

namespace oneCC::Exceptions {

class BadArgumentKey : public std::exception {
public:
    std::string message;
    BadArgumentKey(const char* mes = NULL)
    {
        message = mes == NULL ? "" : std::string(mes);
    }

private:
    virtual const char* what() const throw()
    {
        return ("Argument key should start with - or --, got " + message + " instead").c_str();
    }
};

class MissingArgument : public std::exception {
public:
    std::string message;
    MissingArgument(const char* mes = NULL)
    {
        message = mes == NULL ? "" : std::string(mes);
    }

private:
    virtual const char* what() const throw()
    {
        return ("Missing required argument, " + message).c_str();
    }
};

}