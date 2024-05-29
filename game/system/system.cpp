#include <game/composition/composition.hpp>
#include <game/system/system.h>
#include <game/GameContext.hpp>
#include <SFML/Window.hpp>

void sys::clear_velocity(const GameContext *context)
{
    const auto reg = context->get_registry();
    const auto view = reg->view<game::Paddle, game::Velocity>();
    for (const entt::entity& e : view)
    {
        auto& vel = view.get<game::Velocity>(e);
        vel.Velocity = sf::Vector2i(0,0);
    }
}

void sys::keyboard(const GameContext *context)
{
    const auto reg = context->get_registry();
    const auto view = reg->view<game::Paddle, game::Velocity, game::PlacementLocation>();
    for (const entt::entity& e : view)
    {
        auto [pl, vel] = view.get<game::PlacementLocation, game::Velocity>(e);
        if (pl.Loc == game::Location::RIGHT)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                vel.Velocity.y = -10;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                vel.Velocity.y = 10;
            }
        }
        if (pl.Loc == game::Location::LEFT)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                vel.Velocity.y = -10;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                vel.Velocity.y = 10;
            }
        }
    }
}

void sys::movement(const GameContext *context)
{
    const auto reg = context->get_registry();
    const auto view = reg->view<game::Position, game::Velocity>();
    for (const entt::entity e : view)
    {
        auto [pos, vel] = view.get<game::Position, game::Velocity>(e);
        pos.Position.x += vel.Velocity.x;
        pos.Position.y += vel.Velocity.y;
    }
}

void sys::render(const GameContext *context)
{
    const auto reg = context->get_registry();
    const auto view = reg->view<game::Paddle, game::Position, game::Size, game::RenderTarget>();
    for (const entt::entity e : view)
    {
        auto& shape = view.get<game::Paddle>(e).Shape;
        const auto size = view.get<game::Size>(e).Size;                
        const auto position = view.get<game::Position>(e).Position;
        shape.setSize(size);
        shape.setPosition(position);

        const auto renderTarget = view.get<game::RenderTarget>(e).RenderTarget;
        renderTarget->draw(shape);
    }
}