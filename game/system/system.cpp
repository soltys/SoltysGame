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

void sys::serve(const GameContext *context)
{
    const auto reg = context->get_registry();
    const auto view = reg->view<game::Ball, game::Serve, game::Velocity>();
    auto game_settings = Locator::get_game_settings();
    for (const entt::entity &e : view)
    {
        auto &vel = view.get<game::Velocity>(e);
        auto &serv = view.get<game::Serve>(e);
        if (serv.Loc == game::Direction::Left)
        {
            vel.x = -game_settings->get_ball_base_speed();
            vel.y = 0;
        }
        else
        {
            vel.x = game_settings->get_ball_base_speed();
            vel.y = 0;
        }

        reg->erase<game::Serve>(e);
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
    const auto paddle_view = reg->view<game::Paddle, game::Position, game::Size>();
    for (const entt::entity &paddle_e : paddle_view)
    {
        auto [paddle_pos, paddle_size] = paddle_view.get<game::Position, game::Size>(paddle_e);
        auto paddle_rect = sf::Rect<float>(paddle_pos.to_vector(), paddle_size.to_vector());
        const auto ball_view = reg->view<game::Ball, game::Position, game::Size, game::Velocity>();
        for (const entt::entity &ball_e : ball_view)
        {
            auto [ball_pos, ball_size, ball_vel] = ball_view.get<game::Position, game::Size, game::Velocity>(ball_e);
            auto ball_rect = sf::Rect<float>(ball_pos.to_vector(), ball_size.to_vector(2.f));

            if (ball_rect.intersects(paddle_rect))
            {
                auto &vel = ball_view.get<game::Velocity>(ball_e);
                vel.x = vel.x * -1;
            }
        }
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