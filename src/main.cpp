#include "Game.h"

Game *game = nullptr;

int main(int argc, char *argv[])
{
    game = new Game();

    game->init("Game", 800, 640, false);

    while (game->isRunning())
    {
        game->handleEvents();
        game->update();
        game->render();
    }

    game->clean();

    return 0;
}