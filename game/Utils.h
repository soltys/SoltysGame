#pragma once
#include <string>
#include <vector>
#include <packer/LogEntry.hpp>
namespace r
{
    bool get_toggle(const std::string& name);
    std::vector<char> get_file(const std::string& name);
    std::string get_string(const std::string& key);
}

namespace l
{
    void info(const std::string& logger, const std::string& message);
    void info(const std::string& message);
    std::vector<packer::LogEntry> get_logs(const int amount);
}