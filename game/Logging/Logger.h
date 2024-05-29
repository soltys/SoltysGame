#pragma once
#include <string>
enum LogLevel
{
    INFO,
    WARN,
    ERROR,
};

class Logger
{
public:
public:
    Logger() = default;
    Logger(const Logger &) = default;
    Logger(const Logger &&) = delete;
    Logger &operator=(const Logger &) = default;
    Logger &operator=(Logger &&) = delete;
    virtual ~Logger() = default;

    virtual void log(LogLevel log_level, const std::string &logger, const std::string &message) = 0;

protected:
    const char *to_string(LogLevel log_level)
    {
        switch (log_level)
        {
        case LogLevel::INFO:
            return "INFO";
        case LogLevel::ERROR:
            return "ERROR";
        case LogLevel::WARN:
            return "WARN";
        default:
            return "";
        }
    }
};