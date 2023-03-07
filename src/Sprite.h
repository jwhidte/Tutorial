#pragma once

#include "Game.h"
#include "Media.h"

class Sprite
{
public:
    Sprite(float x, float y, int sizex, int sizey);
    ~Sprite();
    void handleEvents();
    void update();
    void render();
    void jump(bool jump);
private:
    SDL_Rect rect;
    int SIZEX, SIZEY;
    float x_pos, y_pos, x_vel, y_vel,left,right,top,bottom, x_ppos, y_ppos;
    bool running = true, jump_pressed = false, can_jump = true, left_pressed = false, right_pressed = false;
    SDL_Texture* image1;
    SDL_Texture* image2;
    Mix_Chunk* chunk1;
};