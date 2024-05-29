#include <game/Logging/CompositeLogger.h>

void CompositeLogger::log(LogLevel log_level, const std::string &logger_name, const std::string &message)
{
    for (auto &&logger : loggers_)
    {
        logger->log(log_level, logger_name, message);
    }
}

void CompositeLogger::push_back(const std::shared_ptr<Logger> &logger)
{
    loggers_.push_back(logger);
}