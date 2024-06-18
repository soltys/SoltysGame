#pragma once
#include <game/core/ToggleService.hpp>

#include <map>
#include <string>
#include <vector>
#include <tuple>

typedef std::map<std::string, bool> toggle_cache_collection;
typedef std::vector<std::tuple<std::string, bool>> preload_collection;
class MemoryCacheToggleService : public ToggleService
{
    toggle_cache_collection memory_cache;
    ToggleService *source_;

public:
    MemoryCacheToggleService(ToggleService *source) : source_(source), memory_cache() {}
    void preload(const preload_collection &toggle_value_collection);
    bool is_on(const std::string &toggle_name) override;
};
