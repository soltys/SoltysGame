#pragma once
#include "Logger.h"
class NullLogger : public Logger
{
    void log(LogLevel log_level, const std::string &logger, const std::string &message) override;
};