#include "Game.h"
#include "Utils.h"
#include "LogWindow.h"
#include <format>
void Game::Initialize()
{
    this->gameTime = std::make_unique<GameTime>();
    this->context = std::make_unique<GameContext>();

    sf::VideoMode windowSize(800u, 600u);
    this->window = std::make_unique<sf::RenderWindow>(windowSize, r::get_locale_string("WINDOW_TITLE"));
    bool log_window_toggle = r::get_toggle("LOG_WINDOW");
    if (log_window_toggle)
    {
        this->log_window = std::make_unique<LogWindow>();
    }
    l::info("===started game===");
    const int framerateLimit = 60;
    l::info("setFramerateLimit(" + std::to_string(framerateLimit) + ")");
    window->setFramerateLimit(framerateLimit);
}
void Game::Update()
{
    context->setWindowPosition(this->window->getPosition())
        ->setWindowSize(this->window->getSize());
    auto dt = this->gameTime->GetMicroseconds();
    l::info(std::format("dt: {}", dt));
    for (auto event = sf::Event{}; window->pollEvent(event);)
    {
        if (event.type == sf::Event::Closed)
        {
            window->close();
            log_window->close();
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            l::info("MouseButtonPressed");
        }
    }
    log_window->update(dt, this->context);
}
bool Game::IsRunning()
{
    return window->isOpen();
}
void Game::Terminate()
{
}
void Game::Draw()
{
    window->clear();
    window->display();
    log_window->render();
}