#ifndef UNIX_DYN_CALLER_HPP
#define UNIX_DYN_CALLER_HPP

#include <dlfcn.h>
#include <map>
#include <iostream>
#include <functional>

#include "IDynCaller.hpp"
#include "DynCallerException.hpp"

class DynCaller : public IDynCaller
{
    public:
        typedef void* Library;

        ~DynCaller()
        {
            clearCache();
        }

        template <class T>
        T callMethod(const std::string &path, const std::string &method)
        {
            auto it = _libraries.find(path);
            Library library = nullptr;
            T (*symbol)();

            if (it == _libraries.end()) {
                library = dlopen(path.c_str(), RTLD_LAZY);
                _libraries[path] = library;
            } else
                library = it->second;

            if (!library)
                throw DynCallerException("Couldn't find or load the library at path: \"" + path + "\".");

            symbol = reinterpret_cast<T (*)()>(dlsym(library, method.c_str()));

            if (!symbol)
                throw DynCallerException("DL sym error: \"" + std::string(dlerror()) + "\".");

            return (symbol());
        }

        void clearCache()
        {
            for (auto it = _libraries.begin(); it != _libraries.end(); it++)
                if (!dlclose(it->second) && dlerror())
                    throw DynCallerException("DL close error: \"" + std::string(dlerror()) + "\"");

            _libraries.clear();
        }

    private:
        std::map<std::string, Library> _libraries;
};

#endif /* UNIX_DYN_CALLER_HPP */
