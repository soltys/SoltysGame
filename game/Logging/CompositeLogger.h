#pragma once
#include "Logger.h"
#include <vector>
#include <memory>
class CompositeLogger : public Logger
{
private:
    std::vector<std::shared_ptr<Logger>> loggers_;

public:
    CompositeLogger(const std::vector<std::shared_ptr<Logger>>& loggers)
    {
        for (auto &&logger : loggers)
        {
            loggers_.push_back(logger);
        }
    }

    void log(LogLevel log_level, const std::string &logger_name, const std::string &message) override;
};