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

    auto window_style = sf::Style::Default;
    if (r::get_toggle("WINDOW_FULLSCREEN_LAUNCH"))
    {
        window_style = sf::Style::Fullscreen;
    }

    this->window = new sf::RenderWindow(video_mode, r::get_locale_string("WINDOW_TITLE"), window_style);
    this->view.setSize(video_mode.width, video_mode.height);
    view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
    view = mysf::get_letterbox_view(view, video_mode.width, video_mode.height);
    l::info("===started game===");

    context
        ->add_lag(this->gameTime->GetMicroseconds())
        ->set_video_mode(video_mode)
        ->set_registry(reg)
        ->set_main_render_target(window);

    factory::create_paddle(context.get(), sf::Vector2f(10.f, 300.f), game::Location::Left);
    factory::create_paddle(context.get(), sf::Vector2f(video_mode.width - 10.f, 300.f), game::Location::Right);
    factory::create_ball(context.get(), sf::Vector2f(400.f, 300.f));

    lua["ball"] = lua.create_table_with("x", 20, "y", 60);
    lua.set_function("create_ball", [this](float x, float y)
                     { factory::create_ball(this->context.get(), sf::Vector2f(x, y)); });
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

            lua.script(R"(
                create_ball(ball["x"],ball["y"])

                ball["x"] = ball["x"] + 20
                ball["y"] = ball["y"] + 20

            )");
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
    window->clear(sf::Color::Color(0x333333));
    window->setView(view);

    sys::render(this->context.get());
    window->display();
}
