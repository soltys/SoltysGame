#pragma once
#include <entt/entt.hpp>
#include <SFML/System.hpp>
#include <game/composition/composition.hpp>
#include <game/GameContext.hpp>

namespace factory{
    void create_paddle(const GameContext* game_context, sf::Vector2f position, game::Location location);
    void create_ball(const GameContext* game_context, sf::Vector2f position);
}