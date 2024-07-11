#include <SFML/Graphics.hpp>
#include <game/EntityFactory.hpp>
#include <game/Game.hpp>
#include <game/Locator.hpp>
#include <game/Utils.hpp>
#include <game/composition/composition.hpp>
#include <game/config.hpp>
#include <game/core/EnttArchive.hpp>
#include <game/system/system.hpp>

void Game::initialize()
{
    this->time = std::make_unique<GameTime>();
    this->context = std::make_unique<GameContext>();
    this->should_escape_close = r::is_on("ESCAPE_CLOSE_GAME");
    const sf::VideoMode video_mode(800u, 600u);

    auto window_style = sf::Style::Default;
    auto should_fullscreen_launch = r::is_on("WINDOW_FULLSCREEN_LAUNCH");
    if (should_fullscreen_launch)
    {
        window_style = sf::Style::Fullscreen;
    }
    this->reg = std::make_unique<entt::registry>();
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

    context->set_video_mode(video_mode)->set_registry(reg.get())->set_main_render_target(window.get());

    const float paddle_margin = 20.f;
    const float middle_of_screen = video_mode.height / 2;
    factory::create_paddle(context.get(), sf::Vector2f(paddle_margin, middle_of_screen), game::Direction::Left);
    factory::create_paddle(context.get(), sf::Vector2f(video_mode.width - paddle_margin, middle_of_screen),
                           game::Direction::Right);

    factory::create_ball(context.get(), sf::Vector2f(150.f, 150.f), game::Direction::Left);
    factory::create_ball(context.get(), sf::Vector2f(150.f, 150.f), game::Direction::Right);
    factory::create_ball(context.get(), sf::Vector2f(150.f, 150.f), game::Direction::Up);
    factory::create_ball(context.get(), sf::Vector2f(150.f, 150.f), game::Direction::Down);

    factory::create_walls(context.get());
    factory::create_point(context.get(), sf::Vector2f(paddle_margin, middle_of_screen), game::Colors::Cyan);

    if (r::is_on("DEBUG_GRID"))
    {
        factory::create_grid(context.get());
    }

    if (r::is_on("SHOW_FPS"))
    {
        auto fps_entity = factory::create_text(context.get(), sf::Vector2f(20.f, 20.f), sf::Vector2f(20, 20));
        time->set_fps_entity(fps_entity);
    }

    if (r::is_on("SHOW_VERSION"))
    {
        std::string version_string = std::format("ver:{} git:{} pack:{}", PROJECT_VERSION, PROJECT_VERSION_SHORT_SHA1,
                                                 PROJECT_PACK_JSON_SHORT_SHA256);
        factory::create_text(context.get(), version_string, sf::Vector2f(20.f, video_mode.height - 20.f),
                             sf::Vector2f(10.f, 10.f));
    }
}

void Game::update()
{
    time->set_fps_start_time_point();
    context->add_lag(this->time->get_microseconds_duration());

    handle_events();
    update_systems();
    draw();
    time->compute_fps(this->reg.get());
}

void Game::handle_events()
{
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
            auto p = factory::create_point(context.get(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y),
                                           game::Colors::Red);
            factory::add_time_to_live(context.get(), p, 3 * 1000000);
            // l::info(enttarchive::to_json(*this->reg));
            l::error("error sample");
            l::warn("warn sample");
        }
    }
}

void Game::update_systems()
{
    while (this->context->should_update())
    {
        sys::clear_velocity(this->context.get());
        sys::time_to_live(this->context.get());
        sys::serve(this->context.get());
        sys::keyboard(this->context.get());
        sys::collision(this->context.get());
        sys::movement(this->context.get());
    }
}

void Game::draw()
{
    window->clear(sf::Color::Color(0xff, 0, 0));
    window->setView(view);
    sys::render(this->context.get());
    window->display();
}

bool Game::is_running()
{
    return window->isOpen();
}
void Game::terminate()
{
}
