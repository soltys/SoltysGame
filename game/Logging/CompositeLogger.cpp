#include "CompositeLogger.h"

void CompositeLogger::log(LogLevel log_level, const std::string &logger_name, const std::string &message)
{
    for (auto &&logger : loggers_)
    {
        logger->log(log_level, logger_name, message);
    }
}