#include <game/Game.hpp>
#include <game/Utils.hpp>
#include <game/composition/composition.hpp>
#include <game/EntityFactory.hpp>
#include <game/system/system.hpp>
#include <sstream>
#include <game/core/EnttArchive.hpp>
void Game::Initialize()
{
    this->gameTime = std::make_unique<GameTime>();
    this->context = std::make_unique<GameContext>();

    const sf::VideoMode video_mode(800u, 600u);

    auto window_style = sf::Style::Default;
    if (r::get_toggle("WINDOW_FULLSCREEN_LAUNCH"))
    {
        window_style = sf::Style::Fullscreen;
    }
    this->reg = std::make_shared<entt::registry>();
    this->window = std::make_unique<sf::RenderWindow>(video_mode, r::get_locale_string("WINDOW_TITLE"), window_style);
    this->view.setSize(video_mode.width, video_mode.height);
    view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
    view = mysf::get_letterbox_view(view, video_mode.width, video_mode.height);
    l::info("===started game===");

    context
        ->add_lag(this->gameTime->GetMicroseconds())
        ->set_video_mode(video_mode)
        ->set_registry(reg)
        ->set_main_render_target(window.get());

    const float paddle_margin = 20.f;
    factory::create_paddle(context.get(), sf::Vector2f(paddle_margin, 300.f), game::Direction::Left);
    factory::create_paddle(context.get(), sf::Vector2f(video_mode.width - paddle_margin, 300.f), game::Direction::Right);

    factory::create_ball(context.get(), sf::Vector2f(150.f, 150.f), game::Direction::Left);
    factory::create_ball(context.get(), sf::Vector2f(150.f, 150.f), game::Direction::Right);
    factory::create_ball(context.get(), sf::Vector2f(150.f, 150.f), game::Direction::Up);
    factory::create_ball(context.get(), sf::Vector2f(150.f, 150.f), game::Direction::Down);

    factory::create_walls(context.get());
}
void Game::Update()
{
    context
        ->add_lag(this->gameTime->GetMicroseconds());

    for (auto event = sf::Event{}; window->pollEvent(event);)
    {
        if (event.type == sf::Event::Resized)
        {
            view = mysf::get_letterbox_view(view, event.size.width, event.size.height);
        }
        if (event.type == sf::Event::Closed)
        {
            window->close();
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            l::info("MouseButtonPressed");
            l::info(enttarchive::to_json(*this->reg));
        }
    }

    while (this->context->should_update())
    {
        sys::clear_velocity(this->context.get());
        sys::serve(this->context.get());
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
}
void Game::Draw()
{
    window->clear(sf::Color::Color(0x333333));
    window->setView(view);

    sys::render(this->context.get());
    window->display();
}
