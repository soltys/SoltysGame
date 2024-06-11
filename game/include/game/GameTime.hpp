#pragma once
#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <format>
#include <game/composition/composition.hpp>
class GameTime
{
private:
	sf::Clock main_clock;

	std::vector<int> fps_counts;
	std::optional<entt::entity> fps_entity;
	std::chrono::high_resolution_clock::time_point fps_start;
	std::chrono::high_resolution_clock::time_point fps_end;

public:
	GameTime() {}

	void set_fps_entity(entt::entity e)
	{
		fps_entity = e;
	}
	void set_fps_start_time_point()
	{
		fps_start = std::chrono::high_resolution_clock::now();
	}

	int compute_fps(entt::registry *reg)
	{
		fps_end = std::chrono::high_resolution_clock::now();

		auto fps_count = (float)1e9 / (float)std::chrono::duration_cast<std::chrono::nanoseconds>(fps_end - fps_start).count();
		if (fps_counts.size() >= 100)
		{
			fps_counts.erase(fps_counts.begin());
		}
		fps_counts.push_back(fps_count);
		auto computed_fps = std::reduce(fps_counts.begin(), fps_counts.end()) / fps_counts.size();

		if (fps_entity.has_value())
		{
			auto &t = reg->get<game::Text>(fps_entity.value());
			t.text = std::format("FPS: {}", computed_fps);
		}

		return computed_fps;
	}

	sf::Int64 get_microseconds_duration()
	{
		auto dt = main_clock.getElapsedTime().asMicroseconds();
		main_clock.restart();
		return dt;
	}
};
