#pragma once
#include <memory>

#include "GameTime.hpp"

#include <allegro5/display.h>
#include <allegro5/timer.h>
#include <allegro5/events.h>

class Game {
private:
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_TIMER* timer = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_EVENT ev;
	
	void Update(double dt, ALLEGRO_EVENT* ev);

	bool noexit = true;
	bool redraw = true;

	std::unique_ptr<GameTime> gameTime;
public:
	ALLEGRO_EVENT& WaitForEvent() { al_wait_for_event(event_queue, &ev); return ev; }
	void Initialize();
	void Update();
	bool IsRunning();
	void Terminate();
	void Draw();
};
