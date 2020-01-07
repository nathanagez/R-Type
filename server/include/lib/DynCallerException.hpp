#ifndef DYN_CALLER_EXCEPTION_HPP
#define DYN_CALLER_EXCEPTION_HPP

#include <exception>
#include <string>

class DynCallerException : public std::exception {
    public:
        DynCallerException(const std::string &message);
        virtual const char* what() const throw();

    private:
        std::string _message;
};

#endif /* DYN_CALLER_EXCEPTION_HPP */
