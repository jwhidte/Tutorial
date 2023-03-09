#include "Game.h"
#include "Media.h"
#include "Sprite.h"
using std::vector;
SDL_Event Game::event;
int Game::mWidth = 640, Game::mHeight = 200;
int SIZEX = 64, SIZEY = 64;

//SDL Variables
Sprite player = Sprite(100, 100, 64, 64);

vector<vector<int>> Game::tilemap;

bool Game::running = false;
Media Game::media;
// Tilemap variables
int mapWidth, mapHeight = 20;

Game::Game()
{}

Game::~Game()
{}

void Game::throw_sdl_err(const char* fmt)
{
    SDL_LogError(
        SDL_LOG_CATEGORY_APPLICATION,
        fmt,
        SDL_GetError()
    );
}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE);
        renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        running = true;
    }
    else
    {
        running = false;
        printf("epic fail");
    }
	if (Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 1024 ) < 0 ) 
    {
		std::cout << "Error initializing SDL_mixer: " << Mix_GetError() << std::endl;
	}
    if (!IMG_Init(IMG_INIT_PNG))
    {
        std::cout << "Error initializing SDL_IMG: " << IMG_GetError() << std::endl;
    }
    Game::media.addTexture("tile","images/tile.png",renderer);
    Game::media.addTexture("face1","images/Face1.png",renderer);
    Game::media.addTexture("face2","images/Face2.png",renderer);
    Game::tilemap = media.loadTilemap("images/tilemap.txt");
}
void Game::handleEvents()
{
    SDL_PollEvent(&Game::event);
    switch (Game::event.type)
    {
        case SDL_QUIT:
            Game::running = false;
            break;
    case SDL_KEYDOWN:
        switch (Game::event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            Game::running = false;
            break;
        }
        break;
    }
    player.handleEvents();
}
void Game::update()
{
    player.update();

}
void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    player.render(renderer);
    for (int y = 0; y < mapHeight; y++)
    {
        for (int x = 0; x < mapWidth; x++)
        {
            if (tilemap[y][x] == 1)
            {
                SDL_Rect tileRect = { x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
                SDL_RenderCopy(renderer, Game::media.getTexture("tile"), nullptr, &tileRect);
            }
        }
    }
    SDL_RenderPresent(renderer);
    SDL_Delay(1000/FPS);

}
void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}