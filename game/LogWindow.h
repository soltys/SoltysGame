#include <SFML/Graphics.hpp>
#include <memory>
#include "GameContext.hpp"
#pragma once
class LogWindow
{
private:
    std::unique_ptr<sf::RenderWindow> render_window_;
    std::unique_ptr<sf::Text> text_;
    sf::Vector2i last_main_window_position;

    sf::Font font_;
    std::vector<char> font_memory_;
    std::vector<std::string> lines_;

public:
    LogWindow();
    void update(sf::Int64 dt, const std::unique_ptr<GameContext>& context);
    void render();
    void close();
};