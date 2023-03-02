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

const int SPEED= 600;
const int GRAVITY =2000;
const int FPS = 60;
const int JUMP = -1600;
const int TILE_SIZE = 128;

class Game
{
public:
    Game();
    ~Game();

    void init(const char* title, int width, int height, bool fullscreen);
    void throw_sdl_err(const char* fmt);

    static SDL_Renderer *renderer;
    static SDL_Event event;
    static bool running;
    static Media media;
    static std::vector<std::vector<int>> tilemap;
    static int mWidth, mHeight;

private:
    SDL_Window *window;
    
};
