#pragma once
#include <SFML/Graphics.hpp>
#include <game/GameTime.hpp>
#include <game/GameContext.hpp>
#include <entt/entt.hpp>
class Game
{
	void Update(double dt, GameContext ev);

	bool should_escape_close = false;

	std::unique_ptr<GameContext> context;
	std::unique_ptr<GameTime> time;
	std::unique_ptr<sf::RenderWindow> window;
	sf::View view;
	std::unique_ptr<entt::registry> reg = nullptr;

	void handle_events();
	void update_systems();
	void draw();
	
public:
	void initialize();
	void update();
	bool is_running();
	void terminate();
};