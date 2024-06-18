#include <game/core/PackerToggleService.hpp>
#include <game/core/MemoryCacheToggleService.hpp>

#include <vector>
#include <tuple>
#include <string>

#include <game/Locator.hpp>
bool PackerToggleService::is_on(const std::string &toggle_name)
{
    return Locator::get_packer()->is_on(toggle_name);
}

void MemoryCacheToggleService::preload(const preload_collection &toggle_value_collection)
{
    for (const auto &tv : toggle_value_collection)
    {
        memory_cache.emplace(std::get<0>(tv), std::get<1>(tv));
    }
}

bool MemoryCacheToggleService::is_on(const std::string &toggle_name)
{
    if (memory_cache.count(toggle_name) == 0)
    {
        auto is_on = source_->is_on(toggle_name);
        memory_cache.emplace(toggle_name, is_on);
        return is_on;
    }
    else
    {
        return memory_cache.at(toggle_name);
    }
}