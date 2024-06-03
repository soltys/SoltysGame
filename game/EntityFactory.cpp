#include <game/EntityFactory.h>
#include <game/composition/composition.hpp>
#include <SFML/System.hpp>
#include <game/GameContext.hpp>
#include <entt/entt.hpp>
#include <game/Locator.h>
void factory::create_paddle(const GameContext* game_context, sf::Vector2f position, game::Location location)
{
    auto reg = game_context->get_registry();    
    auto render_target = game_context->get_main_render_target();
    auto base_size = Locator::get_game_settings()->get_paddle_base_size();
    entt::entity e = reg->create();
    reg->emplace<game::Paddle>(e, sf::RectangleShape(base_size));
    reg->emplace<game::Position>(e, position);
    reg->emplace<game::Velocity>(e, sf::Vector2i(0, 0));
    reg->emplace<game::Size>(e, base_size);
    reg->emplace<game::PlacementLocation>(e, location);
    reg->emplace<game::RenderTarget>(e, render_target);
}

void factory::create_ball(const GameContext* game_context, sf::Vector2f position)
{
    auto reg = game_context->get_registry();    
    auto render_target = game_context->get_main_render_target();
    auto base_size = Locator::get_game_settings()->get_ball_base_size();
    entt::entity e = reg->create();
    reg->emplace<game::Ball>(e, sf::CircleShape(base_size.x));
    reg->emplace<game::Position>(e, position);
    reg->emplace<game::Velocity>(e, sf::Vector2i(0, 0));
    reg->emplace<game::Size>(e, base_size);
    reg->emplace<game::RenderTarget>(e, render_target);
}