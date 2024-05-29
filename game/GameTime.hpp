#pragma once
#include <SFML/Graphics.hpp>

class GameTime {
private:
	sf::Clock clock;
public:
	GameTime()  {	}

	sf::Int64 GetMicroseconds() {
		auto dt = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		return dt;
	}
};
