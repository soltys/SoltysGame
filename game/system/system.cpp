#include <game/composition/composition.hpp>
#include <game/system/system.h>
#include <game/GameContext.hpp>
#include <SFML/Window.hpp>
#include "render.h"
#include <game/Locator.h>
void sys::clear_velocity(const GameContext *context)
{
    const auto reg = context->get_registry();
    const auto view = reg->view<game::Paddle, game::Velocity>();
    for (const entt::entity &e : view)
    {
        auto &vel = view.get<game::Velocity>(e);
        vel.x = 0;
        vel.y = 0;
    }
}

void sys::keyboard(const GameContext *context)
{
    const auto reg = context->get_registry();
    const auto view = reg->view<game::Paddle, game::Position, game::Size, game::Velocity, game::PlacementLocation>();
    auto key_map = Locator::get_key_map();
    auto game_settings = Locator::get_game_settings();
    auto base_paddle_speed = game_settings->get_paddle_base_speed();
    for (const entt::entity &e : view)
    {
        auto [pl, pos, size, vel] = view.get<game::PlacementLocation, game::Position, game::Size, game::Velocity>(e);

        if (sf::Keyboard::isKeyPressed(key_map->get_key(pl.Loc, "Up")))
        {
            if (pos.y <= 0)
            {
                vel.y = 0;
            }
            else
            {
                vel.y = -base_paddle_speed;
            }
        }
        if (sf::Keyboard::isKeyPressed(key_map->get_key(pl.Loc, "Down")))
        {
            if (pos.y + size.height >= context->get_video_mode().height)
            {
                vel.y = 0;
            }
            else
            {
                vel.y = base_paddle_speed;
            }
        }
    }
}

void sys::collision(const GameContext *context)
{
    const auto reg = context->get_registry();
    const auto view = reg->view<game::Paddle, game::Position, game::Size, game::Velocity>();
    for (const entt::entity &e : view)
    {
        auto [pos, size] = view.get<game::Position, game::Size>(e);
        auto &vel = view.get<game::Velocity>(e);
    }
}

void sys::movement(const GameContext *context)
{
    const auto reg = context->get_registry();
    const auto view = reg->view<game::Position, game::Velocity>();
    for (const entt::entity &e : view)
    {
        auto [pos, vel] = view.get<game::Position, game::Velocity>(e);
        pos.x += vel.x;
        pos.y += vel.y;
    }
}

void sys::render(const GameContext *context)
{
    render_background(context);
    render_paddle(context);
    render_ball(context);
}