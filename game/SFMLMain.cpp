#include <SFML/Graphics.hpp>
#include <packer/Reader.h>

sf::Vector2i set_window_position_sidebyside(sf::RenderWindow &log_window, sf::RenderWindow &main_window)
{
    auto position = main_window.getPosition();
    auto size = main_window.getSize();
    log_window.setPosition(sf::Vector2i(position.x + size.x, position.y));
    return position;
}

int main(int argc, char *argv[])
{
    packer::Reader packer_reader("pack.db");
    auto v = packer_reader.get_key_value("foo");
    auto logWindow = sf::RenderWindow{{800u, 600u}, ("Log window " + v)};
    auto window = sf::RenderWindow{{800u, 600u}, ("CMake SFML Project " + v)};
    window.setFramerateLimit(144);

    auto font_memory = packer_reader.get_file("font_Consolas.ttf");
    sf::Font font;
    font.loadFromMemory(font_memory.data(), font_memory.size());
    std::string lines;
    for (size_t i = 0; i < 100; i++)
    {                
        lines += std::format("{}. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Proin dapibus sit amet augue a vehicula\r\n", i);
    }

    sf::Text text(lines, font);
    text.setCharacterSize(12);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::Red);
    auto last_main_window_position = set_window_position_sidebyside(logWindow, window);

    sf::WindowHandle handle = window.getSystemHandle();

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                logWindow.close();
            }

            if (window.getPosition() != last_main_window_position)
            {
                last_main_window_position = set_window_position_sidebyside(logWindow, window);
            }
        }

        for (auto event = sf::Event{}; logWindow.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                logWindow.close();
            }
        }

        window.clear();
        window.display();

        if (logWindow.isOpen())
        {
            logWindow.clear();
            logWindow.draw(text);
            logWindow.display();
        }
    }
}