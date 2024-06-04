#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

namespace game
{
    enum class Location
    {
        Up,
        Down,
        Left,
        Right
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
        Size() {}
        Size(float w, float h) : width(w), height(h) {}
        const char *name() const { return "size"; }
        float width;
        float height;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(game::Size, width, height);
    };
    struct Position
    {
        const char *name() const { return "position"; }
        float x;
        float y;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(game::Position, x, y);
    };
    struct Velocity
    {
        const char *name() const { return "velocity"; }
        int x;
        int y;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(game::Velocity, x, y);
    };
    struct Controlable
    {
    };
    struct Ai
    {
    };
    struct PlacementLocation
    {
        const char *name() const { return "placement_location"; }
        Location Loc;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(game::PlacementLocation, Loc);
    };
    struct RenderTarget
    {
        sf::RenderTarget *RenderTarget;
    };
}