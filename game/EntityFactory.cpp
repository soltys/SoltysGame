#include <game/EntityFactory.h>
#include <game/composition/composition.hpp>
#include <SFML/System.hpp>
#include <game/GameContext.hpp>
#include <entt/entt.hpp>
#include <game/Locator.h>
void factory::create_paddle(const GameContext *game_context, sf::Vector2f position, game::Direction location)
{
    auto reg = game_context->get_registry();
    auto base_size = Locator::get_game_settings()->get_paddle_base_size();
    entt::entity e = reg->create();
    reg->emplace<game::Paddle>(e);
    reg->emplace<game::Position>(e, position.x, position.y);
    reg->emplace<game::Velocity>(e, 0.f, 0.f);
    reg->emplace<game::Size>(e, base_size);
    reg->emplace<game::PlacementLocation>(e, location);
}

void factory::create_ball(const GameContext *game_context, sf::Vector2f position)
{
    auto reg = game_context->get_registry();
    auto base_size = Locator::get_game_settings()->get_ball_base_size();
    entt::entity e = reg->create();
    reg->emplace<game::Ball>(e);
    reg->emplace<game::Position>(e, position.x, position.y);
    reg->emplace<game::Velocity>(e, 0.f, 0.f);
    reg->emplace<game::Size>(e, base_size);
    reg->emplace<game::Serve>(e, game::Direction::Left);
}