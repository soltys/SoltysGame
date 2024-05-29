#pragma once
#include <SFML/Graphics.hpp>
class PaddleConfig
{
    sf::Vector2f start_position_;
    bool facing_right_;
public:
    PaddleConfig(sf::Vector2f start_position, bool facing_right) : 
    start_position_(start_position),
    facing_right_(facing_right)
    {
    }

    const sf::Vector2f &get_start_position() const { return start_position_; }
    const bool is_facing_right() const { return facing_right_; }

};