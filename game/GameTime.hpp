#pragma once

#include <allegro5/altime.h>

class GameTime {
private:
	double lastTime;
public:
	GameTime(const double lt): lastTime(lt) {	}

	double GetTick() {
		auto now = al_get_time();
		auto dt = now - lastTime;
		lastTime = now;
		return dt;
	}
};
