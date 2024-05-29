#pragma once
#include <SFML/Graphics.hpp>
#include "Config.h"
class GameContext
{
    sf::Vector2i main_window_position;
    sf::Vector2u main_window_size;
    sf::Int64 update_tick;

    static constexpr int framerate_limit = TARGET_FPS;
    static constexpr float microseconds_per_frame = 1 / framerate_limit;

public:
    const sf::Vector2i &get_window_position() const
    {
        return this->main_window_position;
    }
    const sf::Vector2u &get_window_size() const
    {
        return this->main_window_size;
    }
    const sf::Int64 &get_update_tick() const
    {
        return this->update_tick;
    }

    const float get_dt() const
    {
        return this->update_tick / microseconds_per_frame;
    }

    const bool should_redraw() const
    {
        return this->update_tick >= microseconds_per_frame;
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
    GameContext *set_update_tick(sf::Int64 microseconds)
    {
        this->update_tick = microseconds;
        return this;
    }
};

typedef const std::unique_ptr<GameContext> GameContextPtr;
typedef const GameContext* const ConstGameContext;