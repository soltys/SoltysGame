#include <SFML/Graphics.hpp>
#include <memory>
#include "GameContext.hpp"
#include "GameObject.hpp"
#pragma once
class LogWindow: public GameObject
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
    void initialize() override;
    void update(const std::unique_ptr<GameContext>& context) override;
    void render() override;
    void finalize() override;
};