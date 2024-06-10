#pragma once
#include <SFML/Graphics.hpp>
#include <game/GameTime.hpp>
#include <game/GameContext.hpp>
#include <entt/entt.hpp>
#include <chrono>
class Game
{
	void Update(double dt, GameContext ev);

	bool noexit = true;
	bool should_escape_close = false;

	std::vector<char> font_memory;
	sf::Font fps_font;
	sf::Text fps_text;
	int fps_count = 0;
	std::chrono::high_resolution_clock::time_point fps_start;
	std::chrono::high_resolution_clock::time_point fps_end;

	std::unique_ptr<GameContext> context;
	std::unique_ptr<GameTime> gameTime;
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