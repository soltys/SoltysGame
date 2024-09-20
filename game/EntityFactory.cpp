#include <game/EntityFactory.hpp>
#include <game/composition/composition.hpp>
#include <SFML/System.hpp>
#include <game/GameContext.hpp>
#include <entt/entt.hpp>
#include <game/Locator.hpp>
entt::entity factory::create_paddle(const GameContext *game_context, sf::Vector2f position, game::Direction location)
{
    auto reg = game_context->get_registry();
    auto base_size = Locator::get_game_settings()->get_paddle_base_size();
    entt::entity e = reg->create();
    reg->emplace<game::Paddle>(e);
    reg->emplace<game::Position>(e, position.x, position.y - base_size.height / 2);
    reg->emplace<game::Velocity>(e, 0.f, 0.f);
    reg->emplace<game::Size>(e, base_size);
    reg->emplace<game::PlacementLocation>(e, location);
    reg->emplace<game::RenderRectange>(e, game::ShapeStyle::FILL);
    reg->emplace<game::Color>(e, game::Colors::White);
    return e;
}

entt::entity factory::create_ball(const GameContext *game_context, sf::Vector2f position, game::Direction serve_direction)
{
    auto reg = game_context->get_registry();
    auto base_size = Locator::get_game_settings()->get_ball_base_size();
    auto e = reg->create();
    reg->emplace<game::Ball>(e);
    reg->emplace<game::Position>(e, position.x, position.y);
    reg->emplace<game::Velocity>(e, 0.f, 0.f);
    reg->emplace<game::Size>(e, base_size);
    reg->emplace<game::Serve>(e, serve_direction);
    reg->emplace<game::RenderCircle>(e);
    reg->emplace<game::Color>(e, game::Colors::White);
    return e;
}

void create_wall(const GameContext *context, game::Direction location, game::Position position, game::Size size)
{
    auto reg = context->get_registry();
    auto e = reg->create();
    reg->emplace<game::Wall>(e);
    reg->emplace<game::PlacementLocation>(e, location);
    reg->emplace<game::Position>(e, position);
    reg->emplace<game::Size>(e, size);
    reg->emplace<game::RenderRectange>(e, game::ShapeStyle::FILL);
    reg->emplace<game::Color>(e, game::Colors::White);
}

void factory::create_walls(const GameContext *context)
{
    auto video_mode = context->get_video_mode();

    const int wall_thickness = 2;
    const int up_down_wall_margin = 50;

    create_wall(context, game::Direction::Up, {0, up_down_wall_margin}, {(float)video_mode.size.x, wall_thickness});
    create_wall(context, game::Direction::Down, {0, static_cast<float>(video_mode.size.y - up_down_wall_margin)}, {(float)video_mode.size.x, wall_thickness});

    const int left_right_wall_margin = 0;
    create_wall(context, game::Direction::Left, {left_right_wall_margin, 0}, {wall_thickness, (float)video_mode.size.y});
    create_wall(context, game::Direction::Right, {(float)video_mode.size.x - (left_right_wall_margin + wall_thickness), 0}, {wall_thickness, (float)video_mode.size.y});
}

entt::entity factory::create_text(const GameContext *context, sf::Vector2f position, sf::Vector2f size)
{
    return create_text(context, "", position, size);
}

entt::entity factory::create_text(const GameContext *context, std::string text, sf::Vector2f position, sf::Vector2f size)
{
    auto reg = context->get_registry();
    auto e = reg->create();
    reg->emplace<game::Text>(e, text);
    reg->emplace<game::Position>(e, position.x, position.y);
    reg->emplace<game::Size>(e, size.x, size.y);
    reg->emplace<game::Color>(e, game::Colors::White);
    return e;
}

entt::entity factory::create_point(const GameContext *context, sf::Vector2f position, game::Color color)
{
    auto reg = context->get_registry();
    auto e = reg->create();
    reg->emplace<game::RenderPoint>(e);
    reg->emplace<game::Position>(e, position.x, position.y);
    reg->emplace<game::Size>(e, 5.f, 5.f);
    reg->emplace<game::Color>(e, color);
    return e;
}

entt::entity factory::add_time_to_live_sec(const GameContext *context, entt::entity e, int64_t seconds_to_live)
{
    return add_time_to_live(context, e, seconds_to_live * 1000000);
}

entt::entity factory::add_time_to_live(const GameContext *context, entt::entity e, int64_t microseconds_to_live)
{
    auto reg = context->get_registry();
    reg->emplace<game::TimeToLive>(e, microseconds_to_live);
    return e;
}

void factory::create_grid(const GameContext *context)
{
    auto reg = context->get_registry();
    auto video_mode = context->get_video_mode();

    const int grid_width = 64;
    const int grid_height = grid_width;
    int x_count = static_cast<int>(video_mode.size.x / grid_width) + 1;
    int y_count = static_cast<int>(video_mode.size.y / grid_height) + 1;
    for (int x = 0; x < x_count; x++)
    {
        for (int y = 0; y < y_count; y++)
        {
            entt::entity e = reg->create();
            reg->emplace<game::Position>(e, static_cast<float>(grid_width * x), static_cast<float>(grid_height * y));
            reg->emplace<game::Size>(e, grid_width, grid_height);
            reg->emplace<game::RenderRectange>(e, game::ShapeStyle::OUTLINE);
            reg->emplace<game::Color>(e, game::Colors::Green);
        }
    }
}