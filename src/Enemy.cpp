#include "Enemy.h"

Enemy::Enemy(float x, float y, float sizex, float sizey, SDL_Renderer* renderer)
{
  this->x_pos = x;
  this->renderer = renderer;
  this->y_pos = y;
  this->image1 = Media::loadTexture("images/horror.png",renderer);
  this->chunko = Media::loadSound("sounds/thebelltolls.mp3");
  this->SIZEX = sizex;
  this->SIZEY = sizey;
  rect = {x_pos, y_pos, SIZEX, SIZEY};
  spriterect = {(x_pos - (float)0.5*((float)256.0-SIZEX)),(y_pos - (float)0.5*((float)256.0-SIZEY)), 256, 256};
  clock = 30;
}
Enemy::Enemy()
{}
Enemy::~Enemy()
{}
void Enemy::update(int x2, int y2){
    float xdiff = x2-(x_pos+0.5*SIZEX);
    float ydiff = y2-(y_pos+0.5*SIZEY);
    float angle = atan2(ydiff, xdiff);
    x_pos += Game::SPEED2 * cos (angle);
    y_pos += Game::SPEED2 * sin (angle);
    if((std::sqrt(xdiff * xdiff + ydiff * ydiff) <= 256) && (clock == 0)){
        Mix_PlayChannel(-1, chunko, 1);
        Mix_PlayChannel(-1, chunko, 1);
        Mix_PlayChannel(-1, chunko, 1);
        clock = 90;
    }
    rect.x = (int) x_pos;
    rect.y = (int) y_pos;
    spriterect.x = (int)(x_pos - 0.5*(256.0-SIZEX));
    spriterect.y = (int)(y_pos - 0.5*(256.0-SIZEY));
    if(clock>0){
        clock--;
    }
}
void Enemy::render(SDL_Renderer* renderer){
    SDL_RenderCopyF(renderer, image1, NULL, &spriterect);
}