#ifndef ENGINE_EXCEPTION_HPP
#define ENGINE_EXCEPTION_HPP

#include <exception>
#include <string>

class EngineException : public std::exception {
    public:
        EngineException(const std::string &message);
        virtual const char* what() const throw();

    private:
        std::string _message;
};

#endif /* ENGINE_EXCEPTION_HPP */
