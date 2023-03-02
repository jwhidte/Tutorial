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

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

    static SDL_Renderer *renderer;
    static SDL_Event event;
    static bool running;
    static int mWidth, mHeight;
private:
    SDL_Window *window;
    
};
