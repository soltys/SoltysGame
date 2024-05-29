#pragma once
#include <SFML/Graphics.hpp>
#include "GameTime.hpp"
#include "GameContext.hpp"
#include "LogWindow.h"
#include "GameObject.hpp"

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