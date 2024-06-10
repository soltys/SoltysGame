#pragma once
#include <entt/entt.hpp>
#include <SFML/System.hpp>
#include <game/composition/composition.hpp>
#include <game/GameContext.hpp>

namespace factory
{
    void create_paddle(const GameContext *game_context, sf::Vector2f position, game::Direction location);
    void create_ball(const GameContext *game_context, sf::Vector2f position, game::Direction serve_direction);
    void create_walls(const GameContext *context);
    entt::entity create_text(const GameContext* context, sf::Vector2f position, sf::Vector2f size);
}