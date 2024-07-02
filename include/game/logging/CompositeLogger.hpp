#pragma once
#include <game/logging/Logger.hpp>
#include <vector>
#include <memory>
class CompositeLogger : public Logger
{
private:
    std::vector<std::shared_ptr<Logger>> loggers_;
public:
    void log(LogLevel log_level, const std::string &logger_name, const std::string &message) override;
    void push_back(const std::shared_ptr<Logger> &logger); 
};