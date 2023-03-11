#pragma once
#include <stdio.h>
#include <iostream>
#include <stdbool.h>
#include <time.h>
#include <vector>
#include <cmath>
#include <map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

class Media;
class Sprite;
const int mapWidth = 10;
const int mapHeight = 8;
const double JUMPTIME = 34;
const double JUMPHEIGHT = 196;
const int SPEED= 10;
const float GRAVITY = (8*JUMPHEIGHT*pow(JUMPTIME,-2));
const float JUMP = -(4*JUMPHEIGHT*pow(JUMPTIME,-1));
const int FPS = 60;
const int TILE_SIZE = 128;

class Game
{
public:
    Game();
    ~Game();

    void init(const char* title, int width, int height, bool fullscreen);
    void throw_sdl_err(const char* fmt);

    void handleEvents();
    void update();
    void render();
    void clean();
    bool isRunning() { return running; }

    static SDL_Event event;
    static std::vector<std::vector<int>> tilemap;
    static int mWidth, mHeight; 
private:
    Sprite* player;
    SDL_Texture* tile;
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;
};
