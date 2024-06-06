#include <game/composition/composition.hpp>
#include <game/system/system.h>
#include <game/GameContext.hpp>
#include <SFML/Window.hpp>
#include "render.h"

void sys::render_background(const GameContext *context)
{
    auto render_target = context->get_main_render_target();
    auto view_mode = context->get_video_mode();
    sf::RectangleShape blackbg(sf::Vector2f(view_mode.width, view_mode.height));
    blackbg.setFillColor(sf::Color::Black);
    render_target->draw(blackbg);
}

void sys::render_paddle(const GameContext *context)
{
    const auto reg = context->get_registry();
    const auto view = reg->view<game::Paddle, game::Position, game::Size>();
    for (const entt::entity e : view)
    {        
        const auto size = view.get<game::Size>(e);
        const auto position = view.get<game::Position>(e);
        auto shape = sf::RectangleShape(sf::Vector2f(size.width, size.height));        
        shape.setPosition(position.x, position.y);

        const auto renderTarget = context->get_main_render_target();
        renderTarget->draw(shape);
    }
}

void sys::render_ball(const GameContext *context)
{
    const auto reg = context->get_registry();
    const auto view = reg->view<game::Ball, game::Position, game::Size>();
    for (const entt::entity e : view)
    {
        const auto size = view.get<game::Size>(e);
        const auto position = view.get<game::Position>(e);
        auto shape = sf::CircleShape(size.width);
        shape.setPosition(position.x, position.y);

        const auto renderTarget = context->get_main_render_target();
        renderTarget->draw(shape);
    }
}
