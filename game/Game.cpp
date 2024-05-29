#include <game/Game.h>
#include <game/Utils.h>
#include <game/composition/composition.hpp>
#include <game/EntityFactory.h>
#include <game/system/system.h>
void Game::Initialize()
{
    this->gameTime = std::make_unique<GameTime>();
    this->context = std::make_unique<GameContext>();

    const sf::VideoMode video_mode(800u, 600u);
    this->window = new sf::RenderWindow(video_mode, r::get_locale_string("WINDOW_TITLE"));

    l::info("===started game===");

    context
        ->add_lag(this->gameTime->GetMicroseconds())
        ->set_video_mode(video_mode)
        ->set_registry(reg)
        ->set_main_render_target(window);

    factory::create_paddle(context.get(), sf::Vector2f(10.f, 300.f), game::Location::Left);
    factory::create_paddle(context.get(), sf::Vector2f(video_mode.width - 10.f, 300.f), game::Location::Right);
    factory::create_ball(context.get(), sf::Vector2f(400.f, 300.f));
}
void Game::Update()
{
    context
        ->add_lag(this->gameTime->GetMicroseconds());

    for (auto event = sf::Event{}; window->pollEvent(event);)
    {
        if (event.type == sf::Event::Closed)
        {
            window->close();
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            l::info("MouseButtonPressed");
        }
    }

    while (this->context->should_update())
    {
        sys::clear_velocity(this->context.get());
        sys::keyboard(this->context.get());
        sys::collision(this->context.get());
        sys::movement(this->context.get());
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
    sys::render(this->context.get());
    window->display();
}
