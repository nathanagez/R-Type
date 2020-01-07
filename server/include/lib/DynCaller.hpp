#ifndef DYN_CALLER_HPP
#define DYN_CALLER_HPP

#ifdef __gnu_linux__
    #include "UnixDynCaller.hpp"
#elif _WIN32
    #include "WinDynCaller.hpp"
#endif

#endif /* DYN_CALLER_HPP */
