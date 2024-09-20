#include <game/composition/composition.hpp>
#include <game/system/system.hpp>
#include <game/GameContext.hpp>
void sys::collision(const GameContext *context)
{
    const auto reg = context->get_registry();
    const auto ball_view = reg->view<game::Ball, game::Position, game::Size, game::Color, game::Velocity>();
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
            if (ball_rect.findIntersection(wall_rect))
            {
                auto &vel = ball_view.get<game::Velocity>(ball_e);

                // make ball more red ==> more angry
                auto &col = ball_view.get<game::Color>(ball_e);
                const int color_change_step = 5;
                col.blue = col.blue - color_change_step < 0 ? 0 : col.blue - color_change_step;
                col.green = col.green - color_change_step < 0 ? 0 : col.green - color_change_step;

                if (wall_placement.dir == game::Direction::Left || wall_placement.dir == game::Direction::Right)
                {
                    vel.x = vel.x * -1;
                }
                else if (wall_placement.dir == game::Direction::Down || wall_placement.dir == game::Direction::Up)
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
            if (ball_rect.findIntersection(paddle_rect))
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
            if (paddle_rect.findIntersection(wall_rect))
            {
                auto &vel = paddle_view.get<game::Velocity>(paddle_e);
                vel.y = 0;
            }
        }
    }
}
