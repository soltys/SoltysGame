#pragma once
#include <SFML/Graphics.hpp>
#include "Config.h"
class GameContext
{
    sf::Vector2i main_window_position;
    sf::Vector2u main_window_size;
    sf::Int64 lag = 0;

    static constexpr int framerate_limit = 60.f;
    static constexpr float microseconds_per_update = 1000000.f / 60.f;

public:
    const sf::Vector2i &get_window_position() const
    {
        return this->main_window_position;
    }
    const sf::Vector2u &get_window_size() const
    {
        return this->main_window_size;
    }
    const sf::Int64 &get_lag() const
    {
        return this->lag;
    }

    const bool should_update()
    {
        bool should_update = this->lag >= microseconds_per_update;
        if (should_update)
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
};

typedef const std::unique_ptr<GameContext> GameContextPtr;
typedef const GameContext *const ConstGameContext;