#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
namespace game
{
    enum class Location
    {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    enum class Direction
    {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    struct Paddle
    {
        sf::RectangleShape Shape;
    };
    struct Ball
    {
        sf::CircleShape Shape;
    };
    struct Size
    {
        sf::Vector2f Size;
    };
    struct Position
    {
        sf::Vector2f Position;
    };
    struct Velocity
    {
        sf::Vector2i Velocity;
    };
    struct Controlable
    {
    };
    struct Ai
    {
    };
    struct PlacementLocation
    {
        Location Loc;
    };
    struct RenderTarget
    {
        sf::RenderTarget* RenderTarget;
    };
}