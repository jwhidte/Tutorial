#pragma once

#include "Game.h"

const int SPEED= 600;
const int GRAVITY =2000;
const int FPS = 60;
const int JUMP = -1600;
const int TILE_SIZE = 128;

class Sprite
{
    private:

    SDL_Rect rect;
    int SIZEX, SIZEY;
    float x_pos, y_pos, x_vel, y_vel,left,right,top,bottom, x_ppos, y_ppos;
    bool running = true, jump_pressed = false, can_jump = true, left_pressed = false, right_pressed = false;

public:

    Sprite(float x, float y, int sizex, int sizey);
    ~Sprite();
    void handleEvent(SDL_Event &event);
    void update();
    void render(SDL_Renderer *renderer);
    void jump(bool jump);
};