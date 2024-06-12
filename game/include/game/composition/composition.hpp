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
    struct Wall
    {
    };
    struct Size
    {
        Size() {}
        Size(float w, float h) : width(w), height(h) {}
        float width;
        float height;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(game::Size, width, height);

        sf::Vector2f to_vector() const { return sf::Vector2f(width, height); }
        sf::Vector2f to_vector(float scale) const { return sf::Vector2f(width * scale, height * scale); }
    };
    typedef unsigned char uinit8;

    struct Color
    {
        uinit8 red;
        uinit8 green;
        uinit8 blue;
        uinit8 alpha = 255;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(game::Color, red, green, blue, alpha);
        sf::Color to_color() const { return sf::Color(red, green, blue, alpha); }
    };

    namespace Colors
    {
        static Color Black{0, 0, 0};
        static Color White(255, 255, 255);
        static Color Transparent(0, 0, 0, 0);

        static Color Red(255, 0, 0);
        static Color Green(0, 255, 0);
        static Color Blue(0, 0, 255);
        static Color Yellow(255, 255, 0);
        static Color Magenta(255, 0, 255);
        static Color Cyan(0, 255, 255);
    }

    struct Position
    {
        float x;
        float y;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(game::Position, x, y);

        sf::Vector2f to_vector() const { return sf::Vector2f(x, y); }
    };
    struct Velocity
    {
        float x;
        float y;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(game::Velocity, x, y);

        sf::Vector2f to_vector() const { return sf::Vector2f(x, y); }
    };
    struct PlacementLocation
    {
        Direction dir;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(game::PlacementLocation, dir);
    };
    struct Serve
    {
        Direction dir;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(game::Serve, dir);
    };
    enum class ShapeStyle
    {
        FILL,
        OUTLINE
    };
    struct RenderRectange
    {
        ShapeStyle shape_style;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(game::RenderRectange, shape_style);
    };
    struct RenderCircle
    {
    };
    struct Text
    {
        std::string text;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(game::Text, text);
    };
    struct RenderPoint
    {
    };
    struct TimeToLive
    {
        int64_t microseconds;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(game::TimeToLive, microseconds);
    };
}