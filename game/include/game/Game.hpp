#pragma once
#include <SFML/Graphics.hpp>
#include <game/GameTime.hpp>
#include <game/GameContext.hpp>
#include <entt/entt.hpp>
class Game
{
	void Update(double dt, GameContext ev);

	bool noexit = true;
	bool should_escape_close = false;

	std::unique_ptr<GameContext> context;
	std::unique_ptr<GameTime> time;
	std::unique_ptr<sf::RenderWindow> window;
	sf::View view;
	std::shared_ptr<entt::registry> reg = nullptr;

public:
	void initialize();
	void update();
	bool is_running();
	void terminate();
	void draw();
};