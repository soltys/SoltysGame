#include <SFML/Graphics.hpp>
#include <memory>
#pragma once
class LogWindow
{
private:
    std::unique_ptr<sf::RenderWindow> render_window_;
    std::unique_ptr<sf::Text> text_;
    sf::Vector2i last_main_window_position;

    sf::Font font_;
    std::vector<char> font_memory_;

public:
    LogWindow();
    void update(const sf::Vector2i &main_window_position, const sf::Vector2u &main_window_size);
    void render();
    void close();
};