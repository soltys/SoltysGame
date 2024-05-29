#include <game/logging/WindowsDebugLogger.h>
#include <format>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN
void WindowsDebugLogger::log(LogLevel log_level, const std::string &logger, const std::string &message)
{
    auto msg = std::format("WDL: {} {} {}\r\n", to_string(log_level), logger, message);
    OutputDebugString(msg.c_str());
}