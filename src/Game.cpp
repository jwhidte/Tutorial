#include "Game.h"
#include "Media.h"
#include "Sprite.h"
using std::vector;

int mWidth =640;
int mHeight= 200;
int SIZEX = 64, SIZEY = 64;

//SDL Variables
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

bool Game::running = false;

// Tilemap variables
vector<vector<int>> tilemap;
int mapWidth, mapHeight;

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
        if (window)
        {
            std::cout << "Window created!" << std::endl;
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer created!" << std::endl;
        }
        running = true;
    }
    else
    {
        running = false;
    }
    Media media;
    tileTexture = media.loadTexture("assets/tileset.png");
    texture1 = media.loadTexture("assets/texture1.png");
    texture2 = media.loadTexture("assets/texture2.png");
    sound = Mix_LoadWAV("assets/sound.wav");
    loadMap("assets/map.txt");
    player = new Sprite(0, 0, SIZEX, SIZEY);
}
SDL_Texture* tileTexture = nullptr;
SDL_Texture*    texture1 = nullptr;
SDL_Texture*    texture2 = nullptr;
Mix_Chunk*         sound = nullptr;