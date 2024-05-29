#include <game/Logging/ConsoleLogger.h>
#include <iostream>
void ConsoleLogger::log(LogLevel log_level, const std::string &logger, const std::string &message)
{
    std::cout << to_string(log_level) << " " << message << std::endl;
}