#include <game/Game.hpp>
#include <game/Locator.hpp>
int main(int argc, char *argv[])
{
    Locator::initialize();

    Game game;
    game.initialize();
    while (game.is_running())
    {
        game.update();
    }
    game.terminate();
    return 0;
}