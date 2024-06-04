#pragma once
#include <game/composition/composition.hpp>
#include <nlohmann/json.hpp>
#include <entt/entt.hpp>
#include <memory>
#include <game/Utils.h>

class EnttOutputArchive
{
public:
    EnttOutputArchive();

    // persist entity ids
    void operator()(entt::entity entity);
    void operator()(std::underlying_type_t<entt::entity> e);

    template <class T>
    void operator()(T &t)
    {
        current["data"].push_back(t);
        current["name"] = t.name();
    }

    // create a json as string
    const std::string AsString();

    // create bson-data
    const std::vector<uint8_t> AsBson();

private:
    nlohmann::json root;
    nlohmann::json current;
};

class EnttInputArchive
{
private:
    nlohmann::json root;
    nlohmann::json current;

    int root_idx = -1;
    int current_idx = 0;

public:
    EnttInputArchive(const std::string &json_string);
    void next_component();

    void operator()(std::underlying_type_t<entt::entity> &s);
    void operator()(entt::entity &entity);
    template <typename T>
    void operator()(T &t);
};

namespace enttarchive
{
    template <typename SnapshotType, typename ArchiveType>
    void perform_archive_action(SnapshotType& snapshot, ArchiveType& archive);

    std::string to_json(const entt::registry &reg);
    entt::registry from_json(const std::string &json);
}