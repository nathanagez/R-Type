#include <locale>

#include "util/Utils.hpp"

bool Utils::String::isBlank(const std::string &str)
{
    std::locale locale;

    if (isEmpty(str))
        return (true);
    for (unsigned int i = 0; i != str.length(); i += 1)
        if (!std::isspace(str.at(i), locale))
            return (false);
    return (true);
}

bool Utils::String::isEmpty(const std::string &str)
{
    return (str.c_str() == NULL || str.length() == 0);
}

bool Utils::String::isEqual(const std::string &s1, const std::string &s2)
{
    return (s1.compare(s2) == 0);
}

bool Utils::String::isEqualIgnoreCase(const std::string &s1, const std::string &s2)
{
    std::locale locale;

    if (s1.length() != s2.length() || isEmpty(s1) || isEmpty(s2))
        return (false);
    for (unsigned int i = 0; i != s1.length(); i += 1)
        if (std::tolower(s1.at(i), locale) != std::tolower(s2.at(i), locale))
            return (false);
    return (true);
}

std::string Utils::String::toLowerCase(const std::string &str)
{
    std::locale locale;
    std::string s = str;

    for (unsigned int i = 0; i != s.length(); i += 1)
        s.at(i) = std::tolower(s.at(i), locale);
    return (s);
}

std::string Utils::String::toUpperCase(const std::string &str)
{
    std::locale locale;
    std::string s = str;

    for (unsigned int i = 0; i != s.length(); i += 1)
        s.at(i) = std::toupper(s.at(i), locale);
    return (s);
}
