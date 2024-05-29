#include "Game.h"
int main(int argc, char *argv[])
{
    Game game;
    game.Initialize();
    while (game.IsRunning())
    {
        game.Update();

        game.Draw();
    }
    game.Terminate();
    return 0;
}