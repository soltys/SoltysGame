#pragma once
#include <game/Utils.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
class FontService
{
    std::vector<char> default_font_memory;
    std::unique_ptr<sf::Font> default_font;

public:
    FontService()
    {
        default_font_memory = r::get_file("font_Consolas.ttf");
        default_font = std::make_unique<sf::Font>();
        default_font->loadFromMemory(default_font_memory.data(), default_font_memory.size());
    }
    const sf::Font& get_font()
    {
        return *this->default_font;
    }
};
