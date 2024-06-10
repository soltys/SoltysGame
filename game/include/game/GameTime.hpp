#pragma once
#include <SFML/Graphics.hpp>

class GameTime {
private:
	sf::Clock clock;
public:
	GameTime()  {	}

	sf::Int64 get_microseconds() {
		auto dt = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		return dt;
	}
};
