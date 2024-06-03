#include <game/core/KeyMapService.h>
#include <game/Utils.h>
#include <nlohmann/json.hpp>
KeyMapJsonService KeyMapJsonService::parse(std::string json)
{
    KeyMapJsonService key_mapping;
    auto root = nlohmann::json::parse(json);

    for (const auto &el : root.items())
    {
        auto loc = comp::to_location(el.key());
        KeyMap map;
        for (const auto key_map : el.value().items())
        {
            auto key_name = key_map.value().get<std::string>();
            map.emplace(key_map.key(), mysf::to_key(key_name));
        }
        key_mapping.maps.emplace(loc, map);
    }
    return key_mapping;
}