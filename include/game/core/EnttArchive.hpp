#pragma once
#include <game/composition/composition.hpp>
#include <nlohmann/json.hpp>
#include <entt/entt.hpp>
#include <memory>
#include <game/Utils.hpp>

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
    }

    // create a json as string
    const std::string AsString();

    // create bson-data
    const std::vector<uint8_t> AsBson();
    EnttOutputArchive &set_name(std::string n)
    {
        name = n;
        return *this;
    }

private:
    nlohmann::json root;
    nlohmann::json current;
    std::string name;
};

class EnttInputArchive
{
private:
    nlohmann::json root;
    nlohmann::json current;
    std::string name;

    int root_idx = -1;
    int current_idx = 0;

    void next_component();

public:
    EnttInputArchive &set_name(std::string n)
    {
        name = n;
        return *this;
    }
    EnttInputArchive(const std::string &json_string);

    void operator()(std::underlying_type_t<entt::entity> &s);
    void operator()(entt::entity &entity);
    template <typename T>
    void operator()(T &t);
};

namespace enttarchive
{
    template <typename SnapshotType, typename ArchiveType>
    void perform_archive_action(SnapshotType &snapshot, ArchiveType &archive);

    std::string to_json(const entt::registry &reg);
    std::unique_ptr<entt::registry> from_json(std::string &json);
}
