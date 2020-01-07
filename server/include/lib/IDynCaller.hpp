#ifndef I_DYN_CALLER_HPP
#define I_DYN_CALLER_HPP

#include <string>
#include <functional>

class IDynCaller
{
    public:
        virtual ~IDynCaller() = default;

        template <class T>
        T callMethod(const std::string &path, const std::string &method) {};
        virtual void clearCache() = 0;
};

#endif /* I_DYN_CALLER_HPP */
