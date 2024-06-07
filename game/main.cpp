#include <game/Game.hpp>
#include <game/Locator.hpp>
int main(int argc, char *argv[])
{
    Locator::initialize();

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