#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

namespace game
{
    enum class Direction
    {
        Unkown = 0,
        Up,
        Down,
        Left,
        Right
    };

    struct Paddle
    {
    };
    struct Ball
    {
    };
    struct Size
    {
        Size() {}
        Size(float w, float h) : width(w), height(h) {}
        float width;
        float height;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(game::Size, width, height);

        sf::Vector2f to_vector() { return sf::Vector2f(width, height); }
        sf::Vector2f to_vector(float scale) { return sf::Vector2f(width * scale, height * scale); }
    };
    struct Position
    {
        float x;
        float y;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(game::Position, x, y);

        sf::Vector2f to_vector() { return sf::Vector2f(x, y); }
    };
    struct Velocity
    {
        float x;
        float y;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(game::Velocity, x, y);

        sf::Vector2f to_vector() { return sf::Vector2f(x, y); }
    };
    struct PlacementLocation
    {
        Direction Loc;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(game::PlacementLocation, Loc);
    };
    struct Serve
    {
        Direction Loc;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(game::Serve, Loc);
    };
}