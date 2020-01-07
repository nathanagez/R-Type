#include "lib/DynCallerException.hpp"

DynCallerException::DynCallerException(const std::string &message) :
    _message(message)
{
}

const char *DynCallerException::what() const throw()
{
    return (_message.data());
}
