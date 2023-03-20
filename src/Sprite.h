#pragma once

#include "Game.h"
#include "Media.h"

class Sprite
{
public:
    Sprite(float x, float y, float sizex, float sizey, SDL_Renderer* renderer);
    Sprite();
    ~Sprite();
    void handleEvents();
    void update();
    void render(SDL_Renderer* renderer);
    void render2(SDL_Renderer* renderer);
    void jump(bool jump);
    float xCollision();
    float yCollision();
    void windowCollision();
    int getX();
    int getY();
    SDL_FRect rect;
private:
    SDL_FRect rect2;
    float x_pos, y_pos, x_vel, y_vel, x_ppos, y_ppos, SIZEX, SIZEY;
    bool running = true, jump_pressed = false, can_jump = true, left_pressed = false, right_pressed = false, z_pressed = false, x_pressed = false;
    SDL_Texture* image1;
    SDL_Texture* image2;
    SDL_Texture* image3;
    SDL_Renderer* renderer;
    Mix_Chunk* chunk1;
};