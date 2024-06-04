#pragma once
#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>

class GameContext
{
    sf::Vector2i main_window_position;
    sf::Vector2u main_window_size;
    sf::VideoMode video_mode;
    sf::Int64 lag = 0;

    entt::registry *registry;
    sf::RenderTarget *main_render_target;

    static constexpr float frame_limit = 60.f;
    static constexpr int microseconds_per_update = static_cast<int>(1000000.f / frame_limit);

public:
    const sf::Vector2i &get_window_position() const
    {
        return this->main_window_position;
    }
    const sf::Vector2u &get_window_size() const
    {
        return this->main_window_size;
    }
    const sf::VideoMode &get_video_mode() const
    {
        return this->video_mode;
    }
    const sf::Int64 &get_lag() const
    {
        return this->lag;
    }

    entt::registry *get_registry() const
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

    GameContext *set_window_position(const sf::Vector2i position)
    {
        this->main_window_position.x = position.x;
        this->main_window_position.y = position.y;
        return this;
    }
    GameContext *set_window_size(const sf::Vector2u size)
    {
        this->main_window_size.x = size.x;
        this->main_window_size.y = size.y;
        return this;
    }
    GameContext *add_lag(sf::Int64 microseconds)
    {
        this->lag += microseconds;
        return this;
    }
    GameContext *set_video_mode(const sf::VideoMode view_mode)
    {
        this->video_mode = view_mode;
        return this;
    }

    GameContext *set_registry(entt::registry &reg)
    {
        this->registry = &reg;
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