#include <SFML/Graphics.hpp>
#include "LogWindow.h"
#include "Utils.h"
int main(int argc, char *argv[])
{
    auto window = sf::RenderWindow{{800u, 600u}, "Soltys Game"};
    std::shared_ptr<LogWindow> log_window = nullptr;
    bool log_window_toggle = r::get_toggle("LOG_WINDOW");
    if (log_window_toggle)
    {
        log_window = std::make_shared<LogWindow>();
    }

    window.setFramerateLimit(144);

    sf::WindowHandle handle = window.getSystemHandle();

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                if (log_window_toggle)
                    log_window->close();
            }
        }
        if (log_window_toggle)
            log_window->update(window.getPosition(), window.getSize());

        window.clear();
        window.display();
        if (log_window_toggle)
            log_window->render();
    }
}