#include <game/composition/composition.hpp>
#include <game/system/system.hpp>
#include <game/GameContext.hpp>
#include <SFML/Window.hpp>
#include "render.hpp"
#include <game/Locator.hpp>

void sys::render_text(const GameContext *context)
{
    const auto default_font = Locator::get_font_service()->get_font();
    const auto reg = context->get_registry();
    const auto render_target = context->get_main_render_target();
    const auto view = reg->view<game::Text, game::Position, game::Color, game::Size>();
    for (const entt::entity &e : view)
    {
        const auto size = view.get<game::Size>(e);
        const auto t = view.get<game::Text>(e);
        const auto position = view.get<game::Position>(e);
        const auto color = view.get<game::Color>(e);
        sf::Text text(t.text, default_font);
        text.setPosition(position.to_vector());
        text.setCharacterSize(size.height);
        text.setColor(color.to_color());
        render_target->draw(text);
    }
}

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
    for (const entt::entity &e : view)
    {
        const auto render_rectangle = view.get<game::RenderRectange>(e);
        const auto size = view.get<game::Size>(e);
        const auto position = view.get<game::Position>(e);
        const auto color = view.get<game::Color>(e);
        auto shape = sf::RectangleShape(sf::Vector2f(size.width, size.height));
        shape.setPosition(position.x, position.y);
        if (render_rectangle.shape_style == game::ShapeStyle::FILL)
        {
            shape.setFillColor(color.to_color());
        }
        else
        {
            shape.setFillColor(sf::Color::Transparent);
            shape.setOutlineColor(color.to_color());
            shape.setOutlineThickness(0.5f);
        }

        renderTarget->draw(shape);
    }
}

void sys::render_circles(const GameContext *context)
{
    const auto reg = context->get_registry();
    const auto renderTarget = context->get_main_render_target();
    const auto view = reg->view<game::RenderCircle, game::Position, game::Color, game::Size>();
    for (const entt::entity &e : view)
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

void sys::render_points(const GameContext *context)
{
    const auto reg = context->get_registry();
    const auto renderTarget = context->get_main_render_target();
    const auto view = reg->view<game::RenderPoint, game::Position, game::Color, game::Size>();
    for (const entt::entity &e : view)
    {
        const auto size = view.get<game::Size>(e);
        const auto position = view.get<game::Position>(e);
        const auto color = view.get<game::Color>(e);
        sf::VertexArray hline(sf::LinesStrip, 2);
        hline[0].position = sf::Vector2f(position.x - size.width, position.y);
        hline[1].position = sf::Vector2f(position.x + size.width, position.y);
        hline[0].color = color.to_color();
        hline[1].color = color.to_color();

        sf::VertexArray vline(sf::LinesStrip, 2);
        vline[0].position = sf::Vector2f(position.x, position.y - size.height);
        vline[1].position = sf::Vector2f(position.x, position.y + size.height);
        vline[0].color = color.to_color();
        vline[1].color = color.to_color();

        renderTarget->draw(hline);
        renderTarget->draw(vline);
    }
}
