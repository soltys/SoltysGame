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
        if (serv.Dir == game::Direction::Left)
        {
            vel.x = -game_settings->get_ball_base_speed();
            vel.y = 11;
        }
        else if (serv.Dir == game::Direction::Right)
        {
            vel.x = game_settings->get_ball_base_speed();
            vel.y = 7;
        }
        else if (serv.Dir == game::Direction::Up)
        {
            vel.x = 5;
            vel.y = -game_settings->get_ball_base_speed();
        }
        else if (serv.Dir == game::Direction::Down)
        {
            vel.x = 3;
            vel.y = game_settings->get_ball_base_speed();
        }
        else
        {
            throw std::invalid_argument("unexpected value in serve loc");
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

        if (sf::Keyboard::isKeyPressed(key_map->get_key(pl.Dir, "Up")))
        {
            vel.y = -base_paddle_speed;
        }
        if (sf::Keyboard::isKeyPressed(key_map->get_key(pl.Dir, "Down")))
        {
            vel.y = base_paddle_speed;
        }
    }
}

void sys::collision(const GameContext *context)
{
    const auto reg = context->get_registry();
    const auto ball_view = reg->view<game::Ball, game::Position, game::Size, game::Velocity>();
    for (const entt::entity &ball_e : ball_view)
    {
        auto [ball_pos, ball_size, ball_vel] = ball_view.get<game::Position, game::Size, game::Velocity>(ball_e);
        auto ball_rect = sf::Rect<float>(ball_pos.to_vector(), ball_size.to_vector(2.f));

        // BALL collision with walls
        const auto wall_view = reg->view<game::Wall, game::Position, game::PlacementLocation, game::Size>();
        for (const entt::entity &wall_e : wall_view)
        {
            auto [wall_pos, wall_placement, wall_size] = wall_view.get<game::Position, game::PlacementLocation, game::Size>(wall_e);
            auto wall_rect = sf::Rect<float>(wall_pos.to_vector(), wall_size.to_vector());
            if (ball_rect.intersects(wall_rect))
            {
                auto &vel = ball_view.get<game::Velocity>(ball_e);
                if (wall_placement.Dir == game::Direction::Left || wall_placement.Dir == game::Direction::Right)
                {
                    vel.x = vel.x * -1;
                }
                else if (wall_placement.Dir == game::Direction::Down || wall_placement.Dir == game::Direction::Up)
                {
                    vel.y = vel.y * -1;
                }
            }
        }

        // BALL collision with PADDLES
        const auto paddle_view = reg->view<game::Paddle, game::Position, game::Size>();
        for (const entt::entity &paddle_e : paddle_view)
        {
            auto [paddle_pos, paddle_size] = paddle_view.get<game::Position, game::Size>(paddle_e);
            auto paddle_rect = sf::Rect<float>(paddle_pos.to_vector(), paddle_size.to_vector());
            if (ball_rect.intersects(paddle_rect))
            {
                auto &vel = ball_view.get<game::Velocity>(ball_e);
                vel.x = vel.x * -1;
            }
        }
    }

    const auto paddle_view = reg->view<game::Paddle, game::Position, game::Size, game::Velocity>();
    for (const entt::entity &paddle_e : paddle_view)
    {
        auto [paddle_pos, paddle_size, paddle_vel] = paddle_view.get<game::Position, game::Size, game::Velocity>(paddle_e);
        auto paddle_rect = sf::Rect<float>(paddle_pos.to_vector() + paddle_vel.to_vector(), paddle_size.to_vector());

        // PADDLE collision with WALLS
        const auto wall_view = reg->view<game::Wall, game::Position, game::Size>();
        for (const entt::entity &wall_e : wall_view)
        {
            auto [wall_pos, wall_size] = wall_view.get<game::Position, game::Size>(wall_e);
            auto wall_rect = sf::Rect<float>(wall_pos.to_vector(), wall_size.to_vector());
            if (paddle_rect.intersects(wall_rect))
            {
                auto &vel = paddle_view.get<game::Velocity>(paddle_e);
                vel.y = 0;
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
    render_rectangles(context);
    render_circles(context);
}