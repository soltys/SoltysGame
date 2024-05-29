#include <game/composition/composition.hpp>
#include <game/system/system.h>
#include <game/GameContext.hpp>
#include <SFML/Window.hpp>
#include "render.h"

void sys::render_paddle(const GameContext *context)
{
    const auto reg = context->get_registry();
    const auto view = reg->view<game::Paddle, game::Position, game::Size, game::RenderTarget>();
    for (const entt::entity e : view)
    {
        auto &shape = view.get<game::Paddle>(e).Shape;
        const auto size = view.get<game::Size>(e).Size;
        const auto position = view.get<game::Position>(e).Position;
        shape.setSize(size);
        shape.setPosition(position);

        const auto renderTarget = view.get<game::RenderTarget>(e).RenderTarget;
        renderTarget->draw(shape);
    }
}

void sys::render_ball(const GameContext *context)
{
    const auto reg = context->get_registry();
    const auto view = reg->view<game::Ball, game::Position, game::Size, game::RenderTarget>();
    for (const entt::entity e : view)
    {
        auto &shape = view.get<game::Ball>(e).Shape;
        const auto size = view.get<game::Size>(e).Size;
        const auto position = view.get<game::Position>(e).Position;
        shape.setRadius(size.x);
        shape.setPosition(position);

        const auto renderTarget = view.get<game::RenderTarget>(e).RenderTarget;
        renderTarget->draw(shape);
    }
}