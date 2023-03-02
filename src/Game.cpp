#include "Game.h"
#include "Media.h"
#include "Sprite.h"
using std::vector;

int mWidth = 640, mHeight = 200;
int SIZEX = 64, SIZEY = 64;

//SDL Variables
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

vector<vector<int>> Game::tilemap;

bool Game::running = false;
Media Game::media;
// Tilemap variables
int mapWidth, mapHeight;

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
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        }
        running = true;
    }
    else
    {
        running = false;
    }
	if (Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 1024 ) < 0 ) 
    {
		std::cout << "Error initializing SDL_mixer: " << Mix_GetError() << std::endl;
	}
    if (!IMG_Init(IMG_INIT_PNG))
    {
        std::cout << "Error initializing SDL_IMG: " << IMG_GetError() << std::endl;
    }

    media.addTexture("tile","images/tile.png");
    media.addTexture("face1","images/Face1.png");
    media.addTexture("face2","images/Face2.png");
    media.addSound("ding","sounds/DING.mp3");
    tilemap = media.loadTilemap("images/map.txt");
}