#pragma once
#include <game/logging/Logger.hpp>
class NullLogger : public Logger
{
    void log(LogLevel log_level, const std::string &logger, const std::string &message) override;
};