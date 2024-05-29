#include "DbLogger.h"
#include "../Locator.h"
void DbLogger::log(LogLevel log_level, const std::string &logger, const std::string &message)
{
    Locator::get_packer()->insert_log(to_string(log_level), logger, message);
}