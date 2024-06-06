#pragma once
#include <game/composition/composition.hpp>
#include <nlohmann/json.hpp>
#include <entt/entt.hpp>
#include <memory>
#include <game/Utils.h>
#include <game/core/EnttArchive.h>

EnttOutputArchive::EnttOutputArchive()
{
    root = nlohmann::json::array();
    current = nlohmann::json::object();
};

void EnttOutputArchive::operator()(entt::entity entity)
{
    current["ids"].push_back(entity);    
}

void EnttOutputArchive::operator()(std::underlying_type_t<entt::entity> e)
{
    if (!current.empty())
    {
        root.push_back(current);
        current = nullptr;
    }
    current = nlohmann::json::object();
    current["data"] = nlohmann::json::array();
    current["ids"] = nlohmann::json::array();
    current["size"] = e;
}

// create a json as string
const std::string EnttOutputArchive::AsString()
{
    if (!current.empty())
    {
        root.push_back(current);
    }

    return root.dump(2);
}

// create bson-data
const std::vector<uint8_t> EnttOutputArchive::AsBson()
{
    std::vector<std::uint8_t> as_bson = nlohmann::json::to_bson(root);
    return as_bson;
}

EnttInputArchive::EnttInputArchive(const std::string &json_string)
{
    root = nlohmann::json::parse(json_string);
};

void EnttInputArchive::next_component()
{
    root_idx++;
    if (root_idx >= root.size())
    {
        // ERROR
        return;
    }
    current = root.at(root_idx);
    current_idx = 0;
}

void EnttInputArchive::operator()(std::underlying_type_t<entt::entity> &s)
{
    next_component();
    int size = current["size"].get<int>();
    s = (std::underlying_type_t<entt::entity>)size; // pass amount to entt
}

void EnttInputArchive::operator()(entt::entity &entity)
{
    uint32_t ent = current["ids"][current_idx].get<uint32_t>();
    entity = entt::entity(ent);

    //if data is NOT empty current_idx should be increased by EnttInputArchive::operator()(T &t)
    if (current["data"].empty()){        
        current_idx++;
    }
}

template <typename T>
void EnttInputArchive::operator()(T &t)
{
    nlohmann::json component_data = current["data"][current_idx];
    auto comp = component_data.get<T>();
    t = comp;    
    current_idx++;
}

template <typename SnapshotType, typename ArchiveType>
void enttarchive::perform_archive_action(SnapshotType &snapshot, ArchiveType &archive)
{
    snapshot
        .get<game::Paddle>(archive)
        .get<game::Ball>(archive)
        .get<game::Position>(archive)
        .get<game::Size>(archive)
        .get<game::Velocity>(archive)
        .get<game::PlacementLocation>(archive);
}

std::string enttarchive::to_json(const entt::registry &reg)
{
    EnttOutputArchive out;
    auto snapshot = entt::snapshot{reg};
    perform_archive_action(snapshot, out);
    return out.AsString();
}

std::shared_ptr<entt::registry> enttarchive::from_json(std::string &json)
{    
    EnttInputArchive input(json);
    auto reg = std::make_shared<entt::registry>();
    auto loader = entt::snapshot_loader{*reg};
    perform_archive_action(loader, input);
    return reg;
}