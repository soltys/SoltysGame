#include <entt/entt.hpp>
#include <game/composition/composition.hpp>
#include <game/core/EnttArchive.hpp>
#include <memory>
#include <nlohmann/json.hpp>

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
    current["name"] = name;
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

    // if data is NOT empty current_idx should be increased by EnttInputArchive::operator()(T &t)
    if (current["data"].empty())
    {
        current_idx++;
    }
}

template <typename T> void EnttInputArchive::operator()(T &t)
{
    nlohmann::json component_data = current["data"][current_idx];
    auto comp = component_data.get<T>();
    t = comp;
    current_idx++;
}

template <class SnapshotType, class ArchiveType>
void enttarchive::perform_archive_action(SnapshotType &snapshot, ArchiveType &archive)
{
    snapshot.template get<game::Paddle>(archive.set_name("paddle"))
        .template get<game::Ball>(archive.set_name("ball"))
        .template get<game::Wall>(archive.set_name("wall"))
        .template get<game::Position>(archive.set_name("position"))
        .template get<game::Size>(archive.set_name("size"))
        .template get<game::Color>(archive.set_name("color"))
        .template get<game::Velocity>(archive.set_name("velocity"))
        .template get<game::Serve>(archive.set_name("serve"))
        .template get<game::PlacementLocation>(archive.set_name("placement_location"))
        .template get<game::TimeToLive>(archive.set_name("time_to_live"))
        .template get<game::RenderRectange>(archive.set_name("render_rectangle"))
        .template get<game::RenderCircle>(archive.set_name("render_circle"))
        .template get<game::RenderPoint>(archive.set_name("render_point"))
        .template get<game::Text>(archive.set_name("screen_text"));
}

std::string enttarchive::to_json(const entt::registry &reg)
{
    EnttOutputArchive out;
    auto snapshot = entt::snapshot{reg};
    perform_archive_action(snapshot, out);
    return out.AsString();
}

std::unique_ptr<entt::registry> enttarchive::from_json(std::string &json)
{
    EnttInputArchive input(json);
    auto reg = std::unique_ptr<entt::registry>();
    auto loader = entt::snapshot_loader{*reg};
    perform_archive_action(loader, input);
    return reg;
}
