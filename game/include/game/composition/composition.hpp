#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

namespace game
{
    enum class Location
    {
        UNKNOW = 0,
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
    };
    struct Position
    {
        float x;
        float y;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(game::Position, x, y);
    };
    struct Velocity
    {
        float x;
        float y;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(game::Velocity, x, y);
    };
    struct PlacementLocation
    {
        Location Loc;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(game::PlacementLocation, Loc);
    };
}