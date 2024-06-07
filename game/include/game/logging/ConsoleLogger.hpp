#pragma once
#include <game/logging/Logger.hpp>
class ConsoleLogger : public Logger
{
    void log(LogLevel log_level, const std::string &logger, const std::string &message) override;
};