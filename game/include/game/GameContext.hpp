#pragma once
#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>

class GameContext
{
    sf::VideoMode video_mode;
    sf::Int64 lag = 0;

    std::shared_ptr<entt::registry> registry;
    sf::RenderTarget *main_render_target;

    static constexpr float frame_limit = 60.f;
    static constexpr int microseconds_per_update = static_cast<int>(1000000.f / frame_limit);

public:
    const sf::VideoMode &get_video_mode() const
    {
        return this->video_mode;
    }
    GameContext *set_video_mode(const sf::VideoMode view_mode)
    {
        this->video_mode = view_mode;
        return this;
    }
    const sf::Int64 &get_lag() const
    {
        return this->lag;
    }

    std::shared_ptr<entt::registry> get_registry() const
    {
        return this->registry;
    }

    bool should_update()
    {
        if (this->lag >= microseconds_per_update)
        {
            this->lag -= microseconds_per_update;
            return true;
        }
        return false;
    }
    GameContext *add_lag(sf::Int64 microseconds)
    {
        this->lag += microseconds;
        return this;
    }

    GameContext *set_registry(std::shared_ptr<entt::registry> reg)
    {
        this->registry = reg;
        return this;
    }

    GameContext *set_main_render_target(sf::RenderTarget *render_target)
    {
        this->main_render_target = render_target;
        return this;
    }

    sf::RenderTarget *get_main_render_target() const
    {
        return this->main_render_target;
    }
};

typedef const std::unique_ptr<GameContext> GameContextPtr;
typedef const GameContext *const ConstGameContext;