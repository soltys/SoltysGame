#pragma once
#include <string>
#include <vector>
namespace r
{
    bool get_toggle(const std::string& name);
    std::vector<char> get_file(const std::string& name);
    std::string get_string(const std::string& key);
}