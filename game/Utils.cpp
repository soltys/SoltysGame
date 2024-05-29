#include "Utils.h"
#include "Resources.hpp"

bool r::get_toggle(const std::string &name)
{
    return PackerResources::get_packer().get_toggle(name);
}

std::vector<char> r::get_file(const std::string &name)
{
    return PackerResources::get_packer().get_file(name);
}

std::string r::get_string(const std::string &key)
{
    return PackerResources::get_packer().get_key_value(key);
}