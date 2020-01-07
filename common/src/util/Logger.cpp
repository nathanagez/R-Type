#include <fstream>
#include <iostream>
#include <sys/stat.h>

#include "util/Logger.hpp"
#include "util/Utils.hpp"

Logger::LogMode Logger::Instance::_defaultLogMode = Logger::LogMode::Output;
Logger::LogLevel Logger::Instance::_minimumLogLevel = Logger::LogLevel::Info;

Logger::Instance::Instance(const std::string &name) :
    _logMode(_defaultLogMode),
    _name(name),
    _time(Logger::Time())
{
    std::map<std::string, Logger::Instance*>::iterator iterator = _instances.find(name);

    if (iterator == _instances.end())
        _instances.insert(std::pair<std::string, Logger::Instance*>(name, this));
    else {
        _instances.erase(name);
        _instances.insert(std::pair<std::string, Logger::Instance*>(name, this));
    }
}

Logger::Instance::~Instance()
{
}

Logger::Instance *Logger::Instance::get(const std::string &name)
{
    std::map<std::string, Logger::Instance*>::iterator iterator = _instances.find(name);

    if (iterator == _instances.end()) {
        Logger::Instance *logger = new Logger::Instance(name);
        _instances.insert(std::pair<std::string, Logger::Instance*>(name, logger));
        return (logger);
    }
    return (iterator->second);
}

Logger::Instance *Logger::Instance::getGlobalInstance()
{
    return (_globalInstance);
}

void Logger::Instance::setDefaultLogMode(LogMode mode)
{
    _defaultLogMode = mode;
}


void Logger::Instance::setMinimumLogLevel(LogLevel level)
{
    _minimumLogLevel = level;


    GLOBAL_LOGGER->info("Minimum log level changed to [" + Utils::String::toUpperCase(levelToString(level)) + "]");
}

Logger::LogMode Logger::Instance::getLogMode() const
{
    return (_logMode);
}

void Logger::Instance::setLogMode(LogMode mode)
{
    _logMode = mode;
}

std::string Logger::Instance::getTimeFormat() const
{
    return (_time.getFormat());
}

void Logger::Instance::setTimeFormat(const std::string &format)
{
    _time.setFormat(format);
}

void Logger::Instance::debug(const std::string &message)
{
    log(Logger::LogLevel::Debug, message);
}

void Logger::Instance::debug(const std::string &file, const int line, const std::string &message)
{
    std::string msg = "[" + file + ":" + std::to_string(line) + "] " + message;

    log(Logger::LogLevel::Debug, msg);
}

void Logger::Instance::error(const std::string &message)
{
    log(Logger::LogLevel::Error, message);
}

void Logger::Instance::error(const std::string &file, const int line, const std::string &message)
{
    std::string msg = "[" + file + ":" + std::to_string(line) + "] " + message;

    log(Logger::LogLevel::Error, msg);
}

void Logger::Instance::fatal(const std::string &message)
{
    log(Logger::LogLevel::Fatal, message);
}

void Logger::Instance::fatal(const std::string &file, const int line, const std::string &message)
{
    std::string msg = "[" + file + ":" + std::to_string(line) + "] " + message;

    log(Logger::LogLevel::Fatal, msg);
}

void Logger::Instance::info(const std::string &message)
{
    log(Logger::LogLevel::Info, message);
}

void Logger::Instance::info(const std::string &file, const int line, const std::string &message)
{
    std::string msg = "[" + file + ":" + std::to_string(line) + "] " + message;

    log(Logger::LogLevel::Info, msg);
}

void Logger::Instance::log(LogLevel level, const std::string &message)
{
    if (level < _minimumLogLevel)
        return;

    Logger::Log log(level, _name, message, _time.now().toString());

    if (_logMode & Logger::LogMode::Output) {
        switch (level) {
            case Debug:
                std::cout << "\033[90m" << log.toString() << "\033[00;39;49m" << std::endl;
                break;
            case Info:
                std::cout << "\033[37m" << log.toString() << "\033[00;39;49m" << std::endl;
                break;
            case Warning:
                std::cout << "\033[33m" << log.toString() << "\033[00;39;49m" << std::endl;
                break;
            case Error:
                std::cout << "\033[31m" << log.toString() << "\033[00;39;49m" << std::endl;
                break;
            case Fatal:
                std::cout << "\033[41m\033[97m" << log.toString() << "\033[00;39;49m" << std::endl;
                break;
        }
    }
    if (_logMode & Logger::LogMode::File)
        appendFile(_name, log);
}

void Logger::Instance::log(LogLevel level, const std::string &file, const int line, const std::string &message)
{
    if (level < _minimumLogLevel)
        return;

    std::string msg = "[" + file + ":" + std::to_string(line) + "] " + message;
    Logger::Log log(level, _name, msg, _time.now().toString());

    if (_logMode & Logger::LogMode::Output) {
        switch (level) {
            case Debug:
                std::cout << "\033[90m" << log.toString() << "\033[00;39;49m" << std::endl;
                break;
            case Info:
                std::cout << "\033[37m" << log.toString() << "\033[00;39;49m" << std::endl;
                break;
            case Warning:
                std::cout << "\033[33m" << log.toString() << "\033[00;39;49m" << std::endl;
                break;
            case Error:
                std::cout << "\033[31m" << log.toString() << "\033[00;39;49m" << std::endl;
                break;
            case Fatal:
                std::cout << "\033[41m\033[97m" << log.toString() << "\033[00;39;49m" << std::endl;
                break;
        }
    }
    if (_logMode & Logger::LogMode::File)
        appendFile(_name, log);
}

void Logger::Instance::warning(const std::string &message)
{
    log(Logger::LogLevel::Warning, message);
}

void Logger::Instance::warning(const std::string &file, const int line, const std::string &message)
{
    std::string msg = "[" + file + ":" + std::to_string(line) + "] " + message;

    log(Logger::LogLevel::Warning, msg);
}

std::string Logger::Instance::levelToString(Logger::LogLevel level)
{
    switch (level) {
        case Debug:
            return ("debug");
        case Info:
            return ("info");
        case Warning:
            return ("warning");
        case Error:
            return ("error");
        case Fatal:
            return ("fatal");
    }
    return ("");
}

Logger::LogLevel Logger::Instance::levelFromString(const std::string &str)
{
    std::string  s = Utils::String::toLowerCase(str);

    if (s == "debug")
        return (Logger::LogLevel::Debug);
    else if (s == "warning")
        return (Logger::LogLevel::Warning);
    else if (s == "error")
        return (Logger::LogLevel::Error);
    else if (s == "fatal")
        return (Logger::LogLevel::Fatal);
    return (Logger::LogLevel::Info);
}

void Logger::Instance::appendFile(const std::string &fileName, Logger::Log &log)
{
    std::ofstream file;
    struct stat st;
    std::string directory = "";

    if (stat("logs/", &st) == 0 && S_ISDIR(st.st_mode))
        directory = "logs/";
    file.open(directory + fileName + ".logs", std::ios::out | std::ios::app);
    if (file.good()) {
        file.exceptions(file.exceptions() | std::ios::failbit | std::ifstream::badbit);
        file << log.toString() << std::endl;
    }
    file.close();
}

std::map<std::string, Logger::Instance*> Logger::Instance::_instances = std::map<std::string, Logger::Instance*>();
Logger::Instance *Logger::Instance::_globalInstance = new Logger::Instance("Logger");

/* ------------------------------------------------------------------------------------------------------------------ */

Logger::Log::Log(Logger::LogLevel level, const std::string &loggerName, const std::string &message, const std::string &timestamp) :
    _level(level),
    _loggerName(loggerName),
    _message(message),
    _timestamp(timestamp)
{
}

Logger::Log::~Log()
{
}

std::string Logger::Log::toString()
{
    return (_timestamp  + " [" + Utils::String::toUpperCase(Logger::Instance::levelToString(_level)) + "] [" + _loggerName + "] " + _message);
}

/* ------------------------------------------------------------------------------------------------------------------ */

const std::string Logger::Time::days[7][2] = {
    {"Monday", "Mon"},
    {"Tuesday", "Tue"},
    {"Wednesday", "Wed"},
    {"Thursday", "Thu"},
    {"Friday", "Fri"},
    {"Saturday", "Sat"},
    {"Sunday", "Sun"}
};

const std::string Logger::Time::months[12][2] = {
    {"January", "Jan"},
    {"February", "Feb"},
    {"March", "Mar"},
    {"April", "Apr"},
    {"May", "May"},
    {"June", "Jun"},
    {"July", "Jul"},
    {"August", "Aug"},
    {"September", "Sep"},
    {"October", "Oct"},
    {"November", "Nov"},
    {"December", "Dec"}
};

Logger::Time::Time(const std::string &format) :
    _format(format),
    _time(time(NULL))
{
}

Logger::Time::~Time()
{
}

std::string Logger::Time::getFormat() const
{
    return (_format);
}

Logger::Time Logger::Time::setFormat(const std::string &format)
{
    if (Utils::String::isBlank(format))
        return (*this);
    _format = format;
    return (*this);
}

Logger::Time Logger::Time::now()
{
    _time = time(NULL);
    return (*this);
}

/*
    y  ->  year (as int)
    M  ->  month (as int)
    Ms ->  month (as abbreviated string)
    MS ->  month (as string)
    d  ->  day (as int)
    ds ->  day (as abbreviated string)
    dS ->  day (as string)
    dw ->  day of the week
    dy ->  day of the year
    h  ->  hour
    m  ->  minute
    s  ->  second
*/
std::string Logger::Time::toString()
{
    std::string s;
    struct tm *t;

    t = localtime(&_time);
    for (unsigned int i = 0; i != _format.length(); i += 1) {
        switch (_format.at(i)) {
            case 'y':
                s += std::to_string(t->tm_year + 1900);
                break;
            case 'M':
                if (i + 1 != _format.length() && _format.at(i + 1) == 'S')
                    s += months[t->tm_mon][0];
                else if (i + 1 != _format.length() && _format.at(i + 1) == 's')
                    s += months[t->tm_mon][1];
                else {
                    if (t->tm_mon < 10)
                        s += '0';
                    s += std::to_string(t->tm_mon + 1);
                    i -= 1;
                }
                i += 1;
                break;
            case 'd':
                if (i + 1 != _format.length() && _format.at(i + 1) == 'S')
                    s += days[t->tm_wday][0];
                else if (i + 1 != _format.length() && _format.at(i + 1) == 's')
                    s += days[t->tm_wday][1];
                else if (i + 1 != _format.length() && _format.at(i + 1) == 'w')
                    s += std::to_string(t->tm_wday == 0 ? 7 : t->tm_wday);
                else if (i + 1 != _format.length() && _format.at(i + 1) == 'y')
                    s += std::to_string(t->tm_yday + 1);
                else {
                    if (t->tm_mday < 10)
                        s += '0';
                    s += std::to_string(t->tm_mday);
                    i -= 1;
                }
                i += 1;
                break;
            case 'h':
                if (t->tm_hour < 10)
                    s += '0';
                s += std::to_string(t->tm_hour);
                break;
            case 'm':
                if (t->tm_min < 10)
                    s += '0';
                s += std::to_string(t->tm_min);
                break;
            case 's':
                if (t->tm_sec < 10)
                    s += '0';
                s += std::to_string(t->tm_sec);
                break;
            case '\\':
                if (i + 1 != _format.length())
                    i += 1;
                s += _format.at(i);
                break;
            default:
                s += _format.at(i);
        }
    }
    return (s);
}
