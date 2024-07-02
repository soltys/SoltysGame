#pragma once
#include <string>
#include <vector>
#include <packer/LogEntry.hpp>
#include <game/logging/Logger.hpp>
#include <chrono>
#include <game/composition/composition.hpp>
namespace r
{
    bool is_on(const std::string &name);
    std::vector<char> get_file(const std::string &name);
    std::string get_string(const std::string &key);
    std::string get_locale_string(const std::string &key);
    std::vector<packer::LogEntry> get_logs(const int amount);
}
#define SPACE(n)
#define LOG_FUNCTION_DECLARATION(name)                                          \
    void SPACE(1)##name(const std::string &logger, const std::string &message); \
    void SPACE(1)##name(const std::string &message);

namespace l
{
    void log(LogLevel log_level, const std::string &logger, const std::string &message);
    LOG_FUNCTION_DECLARATION(info)
    LOG_FUNCTION_DECLARATION(warn)
    LOG_FUNCTION_DECLARATION(error)
}

namespace epoch
{
    std::chrono::local_time<std::chrono::system_clock::duration> to_local_time_zone(int64_t microseconds_epoch);
    std::string to_time_string(int64_t microseconds_epoch);
    std::string to_datetime_string(int64_t microseconds_epoch);
    std::chrono::system_clock::time_point to_time_point(int64_t microseconds_epoch);
}

namespace comp
{
    const char *to_string(game::Direction location);
    game::Direction to_location(std::string name);
}

namespace mysf
{
    sf::Keyboard::Key to_key(std::string key_name);
    sf::View get_letterbox_view(sf::View view, int windowWidth, int windowHeight);

}