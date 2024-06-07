#include <game/EntityFactory.h>
#include <game/composition/composition.hpp>
#include <SFML/System.hpp>
#include <game/GameContext.hpp>
#include <entt/entt.hpp>
#include <game/Locator.h>
void factory::create_paddle(const GameContext *game_context, sf::Vector2f position, game::Direction location)
{
    auto reg = game_context->get_registry();
    auto base_size = Locator::get_game_settings()->get_paddle_base_size();
    entt::entity e = reg->create();
    reg->emplace<game::Paddle>(e);
    reg->emplace<game::Position>(e, position.x, position.y);
    reg->emplace<game::Velocity>(e, 0.f, 0.f);
    reg->emplace<game::Size>(e, base_size);
    reg->emplace<game::PlacementLocation>(e, location);
    reg->emplace<game::RenderRectange>(e);
    reg->emplace<game::Color>(e, game::Colors::White);
}

void factory::create_ball(const GameContext *game_context, sf::Vector2f position, game::Direction serve_direction)
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
}

void create_wall(const GameContext *context, game::Direction location, game::Position position, game::Size size)
{
    auto reg = context->get_registry();
    auto e = reg->create();
    reg->emplace<game::Wall>(e);
    reg->emplace<game::PlacementLocation>(e, location);
    reg->emplace<game::Position>(e, position);
    reg->emplace<game::Size>(e, size);
    reg->emplace<game::RenderRectange>(e);
    reg->emplace<game::Color>(e, game::Colors::White);
}

void factory::create_walls(const GameContext *context)
{
    auto video_mode = context->get_video_mode();

    const int up_down_wall_margin = 25;
    const int wall_thickness = 5;

    const int left_right_wall_margin = 5;
    create_wall(context, game::Direction::Up, {0, up_down_wall_margin}, {(float)video_mode.width, wall_thickness});
    create_wall(context, game::Direction::Down, {0, static_cast<float>(video_mode.height - up_down_wall_margin)}, {(float)video_mode.width, wall_thickness});

    create_wall(context, game::Direction::Left, {left_right_wall_margin, 0}, {wall_thickness, (float)video_mode.height});
    create_wall(context, game::Direction::Right, {(float)video_mode.width - left_right_wall_margin, 0}, {wall_thickness, (float)video_mode.height});
}
