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
        vel.Velocity = sf::Vector2i(0, 0);
    }
}

void sys::keyboard(const GameContext *context)
{
    const auto reg = context->get_registry();
    const auto view = reg->view<game::Paddle, game::Position, game::Size, game::Velocity, game::PlacementLocation>();
    auto key_map = Locator::get_key_map();
    for (const entt::entity &e : view)
    {
        auto [pl, pos, size, vel] = view.get<game::PlacementLocation, game::Position, game::Size, game::Velocity>(e);

        if (sf::Keyboard::isKeyPressed(key_map->get_key(pl.Loc, "Up")))
        {
            if (pos.Position.y <= 0)
            {
                vel.Velocity.y = 0;
            }
            else
            {
                vel.Velocity.y = -10;
            }
        }
        if (sf::Keyboard::isKeyPressed(key_map->get_key(pl.Loc, "Down")))
        {
            if (pos.Position.y + size.Size.y >= context->get_video_mode().height)
            {
                vel.Velocity.y = 0;
            }
            else
            {
                vel.Velocity.y = 10;
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
        pos.Position.x += vel.Velocity.x;
        pos.Position.y += vel.Velocity.y;
    }
}

void sys::render(const GameContext *context)
{
    render_paddle(context);
    render_ball(context);
}