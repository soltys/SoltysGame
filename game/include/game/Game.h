#pragma once
#include <SFML/Graphics.hpp>
#include <game/GameTime.hpp>
#include <game/GameContext.hpp>
#include <game/logging/LogWindow.h>
#include <entt/entt.hpp>
#include <sol/sol.hpp>
class Game
{
	void Update(double dt, GameContext ev);

	bool noexit = true;
	bool redraw = true;

	std::unique_ptr<GameContext> context;
	std::unique_ptr<GameTime> gameTime;
	sf::RenderWindow* window;
	sf::View view;
	entt::registry reg;
	sol::state lua;
public:
	void Initialize();
	void Update();
	bool IsRunning();
	void Terminate();
	void Draw();
};