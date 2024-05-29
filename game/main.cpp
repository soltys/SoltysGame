#include "Game.h"
using namespace std;


int main() {
	Game game;
	game.Initialize();

	while (game.IsRunning()) {
		game.Update();
		game.Draw();
	}

	game.Terminate();
	return 0;
}