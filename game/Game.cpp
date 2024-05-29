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
    if (r::get_toggle("LOG_WINDOW"))
    {
        this->game_object_collection.push_back(std::make_unique<LogWindow>());
    }
    l::info("===started game===");

    std::for_each(this->game_object_collection.begin(), this->game_object_collection.end(),
                  [](const std::unique_ptr<GameObject> &o)
                  { o->initialize(); });
}
void Game::Update()
{
    context
        ->set_window_position(this->window->getPosition())
        ->set_window_size(this->window->getSize())
        ->set_update_tick(this->gameTime->GetMicroseconds());

    for (auto event = sf::Event{}; window->pollEvent(event);)
    {
        if (event.type == sf::Event::Closed)
        {
            std::for_each(this->game_object_collection.begin(), this->game_object_collection.end(),
                          [](const std::unique_ptr<GameObject> &o)
                          { o->finalize(); });

            window->close();
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            l::info("MouseButtonPressed");
        }
    }

    std::for_each(this->game_object_collection.begin(), this->game_object_collection.end(),
                  [&](const std::unique_ptr<GameObject> &o)
                  { o->update(this->context); });
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
    if (!context->should_redraw())
    {
        return;
    }
    std::for_each(this->game_object_collection.begin(), this->game_object_collection.end(),
                  [](const std::unique_ptr<GameObject> &o)
                  { o->render(); });

    window->clear();
    window->display();
}