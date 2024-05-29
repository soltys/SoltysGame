#include "LogWindow.h"
#include <format>
#include "Utils.h"
#include <iostream>
#include <sstream>
LogWindow::LogWindow()
{
    this->render_window_ = std::make_unique<sf::RenderWindow>(sf::VideoMode(800u, 600u), "Log window");

    font_memory_ = r::get_file("font_Consolas.ttf");
    font_.loadFromMemory(font_memory_.data(), font_memory_.size());
    text_ = std::make_unique<sf::Text>("", font_);    
    text_->setCharacterSize(12);
    text_->setStyle(sf::Text::Bold);
    text_->setFillColor(sf::Color::Red);
}

void LogWindow::update(const sf::Vector2i &main_window_position, const sf::Vector2u &main_window_size)
{
    if (main_window_position != last_main_window_position)
    {
        render_window_->setPosition(sf::Vector2i(main_window_position.x + main_window_size.x, main_window_position.y));
        last_main_window_position = main_window_position;
    }

    for (auto event = sf::Event{}; this->render_window_->pollEvent(event);)
    {
        if (event.type == sf::Event::Closed)
        {
            this->render_window_->close();
        }
    }

    auto logs = l::get_logs(40);
    this->lines_.clear();
    for (const auto &l : logs)
    {
        this->lines_.push_back(std::format("t:{}, m:{}", l.date(), l.message()));
    }

    const char *const delim = "\r\n";
    std::ostringstream imploded;
    std::copy(lines_.begin(), lines_.end(),
              std::ostream_iterator<std::string>(imploded, delim));
    text_->setString(imploded.str());
}

void LogWindow::render()
{
    if (this->render_window_->isOpen())
    {
        this->render_window_->clear();
        this->render_window_->draw(*text_);
        this->render_window_->display();
    }
}

void LogWindow::close()
{
    this->render_window_->close();
}