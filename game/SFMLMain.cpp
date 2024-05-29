#include <SFML/Graphics.hpp>
#include <packer/Reader.h>

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

    sf::Text text("hello", font);
    text.setCharacterSize(30);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::Red);

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                logWindow.close();
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