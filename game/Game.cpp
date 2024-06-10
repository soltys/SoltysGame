#include <game/Game.hpp>
#include <game/Utils.hpp>
#include <game/composition/composition.hpp>
#include <game/EntityFactory.hpp>
#include <game/system/system.hpp>
#include <game/core/EnttArchive.hpp>
#include <SFML/Graphics.hpp>
#include <game/Locator.hpp>
void Game::initialize()
{
    this->gameTime = std::make_unique<GameTime>();
    this->context = std::make_unique<GameContext>();
    this->should_escape_close = r::get_toggle("ESCAPE_CLOSE_GAME");
    const sf::VideoMode video_mode(800u, 600u);

    auto window_style = sf::Style::Default;
    auto should_fullscreen_launch = r::get_toggle("WINDOW_FULLSCREEN_LAUNCH");
    if (should_fullscreen_launch)
    {
        window_style = sf::Style::Fullscreen;
    }
    this->reg = std::make_shared<entt::registry>();
    this->window = std::make_unique<sf::RenderWindow>(video_mode, r::get_locale_string("WINDOW_TITLE"), window_style);

    this->view.setSize(video_mode.width, video_mode.height);
    this->view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
    if (should_fullscreen_launch)
    {
        auto desktop_modes = sf::VideoMode::getFullscreenModes();
        auto desktop_mode = desktop_modes[0];
        this->view = mysf::get_letterbox_view(view, desktop_mode.width, desktop_mode.height);
    }
    else
    {
        this->view = mysf::get_letterbox_view(view, video_mode.width, video_mode.height);
    }

    l::info("===started game===");

    context
        ->add_lag(this->gameTime->get_microseconds())
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

    this->font_memory = r::get_file("font_Consolas.ttf");
    fps_font.loadFromMemory(font_memory.data(), font_memory.size());
    fps_text.setFont(fps_font);
    fps_text.setPosition(20, 20);
    fps_text.setCharacterSize(24);
    fps_text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    fps_text.setColor(sf::Color::Red);
}
void Game::update()
{
    fps_start = std::chrono::high_resolution_clock::now();
    context
        ->add_lag(this->gameTime->get_microseconds());

    for (auto event = sf::Event{}; window->pollEvent(event);)
    {
        if (event.type == sf::Event::Resized)
        {
            view = mysf::get_letterbox_view(view, event.size.width, event.size.height);
        }
        else if (event.type == sf::Event::Closed)
        {
            window->close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            if (this->should_escape_close && event.key.code == sf::Keyboard::Escape)
            {
                window->close();
            }

            Locator::get_game_input()->on_key_pressed((int)event.key.code);
        }
        else if (event.type == sf::Event::KeyReleased)
        {
            Locator::get_game_input()->on_key_released((int)event.key.code);
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
bool Game::is_running()
{
    return window->isOpen();
}
void Game::terminate()
{
}
void Game::draw()
{
    window->clear(sf::Color::Color(0xff, 0, 0));
    window->setView(view);

    sys::render(this->context.get());
    
    fps_text.setString(std::format("FPS: {}", fps_count));
    window->draw(fps_text);

    window->display();
    fps_end = std::chrono::high_resolution_clock::now();
    fps_count = (float)1e9 / (float)std::chrono::duration_cast<std::chrono::nanoseconds>(fps_end - fps_start).count();
}
