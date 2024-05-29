#pragma once
#include <SFML/Graphics.hpp>
class GameContext
{
    sf::Vector2i main_window_position;
    sf::Vector2u main_window_size;
    sf::Int64 update_tick;

public:
    const sf::Vector2i& getWindowPosition() const
    {
        return this->main_window_position;
    }
    const sf::Vector2u& getWindowSize() const
    {
        return this->main_window_size;
    }
    const sf::Int64& get_update_tick() const
    {
        return this->update_tick;
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
    GameContext *set_update_tick(sf::Int64 tick)
    {
        this->update_tick = tick;
        return this;
    }
};