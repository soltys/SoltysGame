#include <game/Game.h>
#include <game/Utils.h>
#include <game/Logging/LogWindow.h>
#include <game/Paddle.h>
#include <format>
void Game::Initialize()
{
    this->gameTime = std::make_unique<GameTime>();
    this->context = std::make_unique<GameContext>();

    const sf::VideoMode video_mode(800u, 600u);
    this->window = new sf::RenderWindow(video_mode, r::get_locale_string("WINDOW_TITLE"));
    if (r::get_toggle("LOG_WINDOW"))
    {
        this->game_object_collection.push_back(std::make_unique<LogWindow>());
    }

    this->game_object_collection.push_back(
        std::make_unique<Paddle>(std::make_unique<PaddleConfig>(sf::Vector2f(20, 300), true)));
    this->game_object_collection.push_back(
        std::make_unique<Paddle>(std::make_unique<PaddleConfig>(sf::Vector2f(video_mode.width - 20, 300), false)));

    l::info("===started game===");

    context
        ->set_window_position(this->window->getPosition())
        ->set_window_size(this->window->getSize())
        ->add_lag(this->gameTime->GetMicroseconds())
        ->set_video_mode(video_mode);

    std::ranges::for_each(this->game_object_collection,
                          [&](const std::unique_ptr<GameObject> &o)
                          { o->initialize(this->context.get()); });
}
void Game::Update()
{
    context
        ->set_window_position(this->window->getPosition())
        ->set_window_size(this->window->getSize())
        ->add_lag(this->gameTime->GetMicroseconds());

    for (auto event = sf::Event{}; window->pollEvent(event);)
    {
        if (event.type == sf::Event::Closed)
        {
            std::ranges::for_each(this->game_object_collection,
                                  [](const std::unique_ptr<GameObject> &o)
                                  { o->finalize(); });

            window->close();
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            l::info("MouseButtonPressed");
        }
    }

    while (this->context->should_update())
    {
        std::ranges::for_each(this->game_object_collection,
                              [&](const std::unique_ptr<GameObject> &o)
                              { o->update(this->context.get()); });
    }
}
bool Game::IsRunning()
{
    return window->isOpen();
}
void Game::Terminate()
{
    delete window;
}
void Game::Draw()
{
    window->clear(sf::Color::Black);

    std::ranges::for_each(this->game_object_collection,
                          [&](const std::unique_ptr<GameObject> &o)
                          { o->render(window); });

    window->display();
}
