#include "EngineException.hpp"

EngineException::EngineException(const std::string &message) :
    _message(message)
{
}

const char *EngineException::what() const throw()
{
    return (_message.data());
}