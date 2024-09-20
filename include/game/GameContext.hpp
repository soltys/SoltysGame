#pragma once
#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>

class GameContext
{
    sf::VideoMode video_mode;
    std::int64_t lag = 0;

    entt::registry* registry;
    sf::RenderTarget *main_render_target;

    static constexpr float frame_limit = 60.f;
    
public:
    static constexpr int microseconds_per_update = static_cast<int>(1000000.f / frame_limit);
    
    const sf::VideoMode &get_video_mode() const
    {
        return this->video_mode;
    }
    GameContext *set_video_mode(const sf::VideoMode view_mode)
    {
        this->video_mode = view_mode;
        return this;
    }
    const std::int64_t &get_lag() const
    {
        return this->lag;
    }

    entt::registry* get_registry() const
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
    GameContext *add_lag(std::int64_t microseconds)
    {
        this->lag += microseconds;
        return this;
    }

    GameContext *set_registry(entt::registry* reg)
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