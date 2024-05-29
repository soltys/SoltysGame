#pragma once
#include <SFML/Graphics.hpp>
#include <game/GameTime.hpp>
#include <game/GameContext.hpp>
#include <game/Logging/LogWindow.h>
#include <game/GameObject.hpp>

class Game
{
	void Update(double dt, GameContext ev);

	bool noexit = true;
	bool redraw = true;

	std::unique_ptr<GameContext> context;
	std::unique_ptr<GameTime> gameTime;
	sf::RenderWindow* window;
	GameObjectCollection game_object_collection;

public:
	void Initialize();
	void Update();
	bool IsRunning();
	void Terminate();
	void Draw();
};