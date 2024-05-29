#pragma once
#include <SFML/Graphics.hpp>
class GameContext
{
    sf::Vector2i main_window_position;
    sf::Vector2u main_window_size;

public:
    sf::Vector2i getWindowPosition() const
    {
        return this->main_window_position;
    }
    sf::Vector2u getWindowSize() const
    {
        return this->main_window_size;
    }
    GameContext *setWindowPosition(const sf::Vector2i position)
    {
        this->main_window_position.x = position.x;
        this->main_window_position.y = position.y;
        return this;
    }
    GameContext *setWindowSize(const sf::Vector2u size)
    {
        this->main_window_size.x = size.x;
        this->main_window_size.y = size.y;
        return this;
    }
};