#pragma once
#include <chrono>
#include <game/composition/composition.hpp>
#include <game/logging/Logger.hpp>
#include <packer/LogEntry.hpp>
#include <string>
#include <vector>
namespace r
{
bool is_on(const std::string &name);
std::vector<char> get_file(const std::string &name);
std::string get_string(const std::string &key);
std::string get_locale_string(const std::string &key);
std::vector<packer::LogEntry> get_logs(const int amount);
} // namespace r
namespace l
{
void log(LogLevel log_level, const std::string &logger, const std::string &message);

void info(const std::string &logger, const std::string &message);
void info(const std::string &message);

void warn(const std::string &logger, const std::string &message);
void warn(const std::string &message);

void error(const std::string &logger, const std::string &message);
void error(const std::string &message);
} // namespace l

namespace epoch
{
std::chrono::local_time<std::chrono::system_clock::duration> to_local_time_zone(int64_t microseconds_epoch);
std::string to_time_string(int64_t microseconds_epoch);
std::string to_datetime_string(int64_t microseconds_epoch);
std::chrono::system_clock::time_point to_time_point(int64_t microseconds_epoch);
} // namespace epoch

namespace comp
{
const char *to_string(game::Direction location);
game::Direction to_location(std::string name);
} // namespace comp

namespace mysf
{
sf::Keyboard::Key to_key(std::string key_name);
sf::View get_letterbox_view(sf::View view, int windowWidth, int windowHeight);

} // namespace mysf
