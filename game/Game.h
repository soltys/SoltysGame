#pragma once
#include <SFML/Graphics.hpp>
#include "GameTime.hpp"
#include "GameContext.hpp"
#include "LogWindow.h"
class Game {
	void Update(double dt, GameContext ev);

	bool noexit = true;
	bool redraw = true;

    std::unique_ptr<GameContext> context;
	std::unique_ptr<GameTime> gameTime;
	std::unique_ptr<sf::RenderWindow> window;
	std::unique_ptr<LogWindow> log_window;
    
public:
	void Initialize();
	void Update();
	bool IsRunning();
	void Terminate();
	void Draw();
};