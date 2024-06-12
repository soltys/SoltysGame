#pragma once
#include <entt/entt.hpp>
#include <SFML/System.hpp>
#include <game/composition/composition.hpp>
#include <game/GameContext.hpp>

namespace factory
{
    entt::entity create_paddle(const GameContext *game_context, sf::Vector2f position, game::Direction location);
    entt::entity create_ball(const GameContext *game_context, sf::Vector2f position, game::Direction serve_direction);
    void create_walls(const GameContext *context);
    entt::entity create_text(const GameContext *context, sf::Vector2f position, sf::Vector2f size);
    entt::entity create_text(const GameContext *context, std::string text, sf::Vector2f position, sf::Vector2f size);
    entt::entity create_point(const GameContext *context, sf::Vector2f position, game::Color color);

    entt::entity add_time_to_live(const GameContext *context, entt::entity e, int64_t microseconds_to_live);
    entt::entity add_time_to_live_sec(const GameContext *context, entt::entity e, int64_t seconds_to_live);
}