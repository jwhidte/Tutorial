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
class Enemy;
const double JUMPTIME = 40;
const double JUMPHEIGHT = 256;
const int SPEED= 10;
const float GRAVITY = (8*JUMPHEIGHT*pow(JUMPTIME,-2));
const float JUMP = -(4*JUMPHEIGHT*pow(JUMPTIME,-1));
const int FPS = 60;

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
    static float SPEED2, TILE_SIZE; 
private:
    Sprite* player;
    Enemy* enemy;
    Mix_Music* gMusic;
    SDL_Texture* tile;
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;
};
