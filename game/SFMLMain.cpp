#include <SFML/Graphics.hpp>
#include <packer/Reader.h>

int main()
{
    packer::Reader packer_reader("my_own_pack.sqlite");
    auto v =  packer_reader.get_key_value("foo");
    auto window = sf::RenderWindow{ { 1920u, 1080u }, ("CMake SFML Project " + v) };
    window.setFramerateLimit(144);

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        window.display();
    }
}