#include <game/composition/composition.hpp>
#include <game/system/system.hpp>
#include <game/GameContext.hpp>
#include <SFML/Window.hpp>
#include "render.hpp"
#include <game/Locator.hpp>
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

void sys::time_to_live(const GameContext *context)
{
    const auto reg = context->get_registry();
    const auto view = reg->view<game::TimeToLive>();
    for (const entt::entity &e : view)
    {
        auto &ttl = view.get<game::TimeToLive>(e);
        if (ttl.microseconds < 0)
        {
            reg->destroy(e);
            continue;
        }

        ttl.microseconds -= GameContext::microseconds_per_update;
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
        if (serv.dir == game::Direction::Left)
        {
            vel.x = -game_settings->get_ball_base_speed();
            vel.y = 11;
        }
        else if (serv.dir == game::Direction::Right)
        {
            vel.x = game_settings->get_ball_base_speed();
            vel.y = 7;
        }
        else if (serv.dir == game::Direction::Up)
        {
            vel.x = 5;
            vel.y = -game_settings->get_ball_base_speed();
        }
        else if (serv.dir == game::Direction::Down)
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
    const auto view = reg->view<game::Paddle, game::Velocity, game::PlacementLocation>();
    auto key_map = Locator::get_key_map();
    auto game_settings = Locator::get_game_settings();
    auto game_input = Locator::get_game_input();
    auto base_paddle_speed = game_settings->get_paddle_base_speed();
    for (const entt::entity &e : view)
    {
        auto [pl, vel] = view.get<game::PlacementLocation, game::Velocity>(e);

        auto action_up_key = key_map->get_key(pl.dir, Action::UP);
        if (game_input->is_key_pressed((int)action_up_key))
        {
            vel.y = -base_paddle_speed;
        }
        auto action_down_key = key_map->get_key(pl.dir, Action::DOWN);
        if (game_input->is_key_pressed((int)action_down_key))
        {
            vel.y = base_paddle_speed;
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
    render_text(context);
    render_points(context);
}