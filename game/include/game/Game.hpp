#pragma once
#include <SFML/Graphics.hpp>
#include <game/GameTime.hpp>
#include <game/GameContext.hpp>
#include <entt/entt.hpp>
class Game
{
	void Update(double dt, GameContext ev);

	bool noexit = true;
	bool redraw = true;

	std::unique_ptr<GameContext> context;
	std::unique_ptr<GameTime> gameTime;
	std::unique_ptr<sf::RenderWindow> window;
	sf::View view;
	std::shared_ptr<entt::registry> reg = nullptr;
public:
	void Initialize();
	void Update();
	bool IsRunning();
	void Terminate();
	void Draw();
};