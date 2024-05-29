#pragma once
#include <string>
#include <vector>
#include <packer/LogEntry.hpp>
#include <chrono>
namespace r
{
    bool get_toggle(const std::string &name);
    std::vector<char> get_file(const std::string &name);
    std::string get_string(const std::string &key);
    std::string get_locale_string(const std::string &key);
}

namespace l
{
    void info(const std::string &logger, const std::string &message);
    void info(const std::string &message);
    std::vector<packer::LogEntry> get_logs(const int amount);
}

namespace epoch
{
    std::chrono::local_time<std::chrono::system_clock::duration> to_local_time_zone(int64_t microseconds_epoch);
    std::string to_time_string(int64_t microseconds_epoch);
    std::string to_datetime_string(int64_t microseconds_epoch);
    std::chrono::system_clock::time_point to_time_point(int64_t microseconds_epoch);
}
