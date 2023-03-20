#pragma once

#include "Game.h"
#include "Media.h"

class Enemy
{
public:
    Enemy(float x, float y, float sizex, float sizey, SDL_Renderer* renderer);
    Enemy();
    ~Enemy();
    void update(int x2, int y2);
    void render(SDL_Renderer* renderer);
    SDL_FRect rect;
private:
    SDL_FRect spriterect;
    float x_pos, y_pos, SIZEX, SIZEY;
    SDL_Texture* image1;
    SDL_Renderer* renderer;
    Mix_Chunk* chunko;
    int clock = 0;
};