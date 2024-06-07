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

void sys::render_rectangles(const GameContext *context)
{
    const auto reg = context->get_registry();
    const auto renderTarget = context->get_main_render_target();
    const auto view = reg->view<game::RenderRectange, game::Position, game::Color, game::Size>();
    for (const entt::entity& e : view)
    {        
        const auto size = view.get<game::Size>(e);
        const auto position = view.get<game::Position>(e);
        const auto color = view.get<game::Color>(e);
        auto shape = sf::RectangleShape(sf::Vector2f(size.width, size.height));        
        shape.setPosition(position.x, position.y);
        shape.setFillColor(color.to_color());        
        renderTarget->draw(shape);
    }
}

void sys::render_circles(const GameContext *context)
{
    const auto reg = context->get_registry();
    const auto renderTarget = context->get_main_render_target();
    const auto view = reg->view<game::RenderCircle, game::Position, game::Color, game::Size>();
    for (const entt::entity& e : view)
    {
        const auto size = view.get<game::Size>(e);
        const auto position = view.get<game::Position>(e);
        const auto color = view.get<game::Color>(e);
        auto shape = sf::CircleShape(size.width);
        shape.setPosition(position.x, position.y);
        shape.setFillColor(color.to_color());        
        renderTarget->draw(shape);
    }
}
