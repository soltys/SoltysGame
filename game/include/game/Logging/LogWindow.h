#include <SFML/Graphics.hpp>
#include <memory>
#include <game/GameContext.hpp>
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
    void initialize(ConstGameContext context);
    void update(ConstGameContext context);
    void render(sf::RenderTarget *target);
    void finalize();
};