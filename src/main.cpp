#include "Game.h"

Game *game = nullptr;

int main(int argc, char *argv[])
{
    game = new Game();

    game->init("Game", 800, 640, false);

    while (game->isRunning())
    {
        fflush(stdout);
        game->handleEvents();
        game->update();
        game->render();
    }

    game->clean();
    printf("Gaaaaaaaaaah");
    return 0;
}