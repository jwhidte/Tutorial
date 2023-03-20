#include "Sprite.h"

Sprite::Sprite(float x, float y, float sizex, float sizey, SDL_Renderer* renderer)
{
  this->x_pos = x;
  this->renderer = renderer;
  this->y_pos = y;
  this->image1 = Media::loadTexture("images/Face1.png",renderer);
  this->image2 = Media::loadTexture("images/Face2.png",renderer);
  this->image3 = Media::loadTexture("images/Face3.png",renderer);
  this->chunk1 = Media::loadSound("sounds/DING.mp3");
  this->SIZEX = sizex;
  this->SIZEY = sizey;
  rect = {x_pos, y_pos, SIZEX, SIZEY};
  rect2 = {x_pos, y_pos, SIZEX, SIZEY};
}
Sprite::Sprite()
{}
Sprite::~Sprite()
{}
void Sprite::handleEvents(){
    if (Game::event.type == SDL_KEYDOWN){
        switch (Game::event.key.keysym.scancode){
            case SDL_SCANCODE_SPACE:
                jump_pressed = true;
                break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_LEFT:
                left_pressed = true;
                break;
            case SDL_SCANCODE_D:
            case SDL_SCANCODE_RIGHT:
                right_pressed = true;
                break;
            case SDL_SCANCODE_Z:
                z_pressed = true;
                break;
            case SDL_SCANCODE_X:
                x_pressed = true;
                break;
            default:
                break;
        }
    }
    if (Game::event.type == SDL_KEYUP){
        switch (Game::event.key.keysym.scancode){
            case SDL_SCANCODE_SPACE:
                jump_pressed = false;
                y_vel/=2;
                break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_LEFT:
                left_pressed = false;
                break;
            case SDL_SCANCODE_D:
            case SDL_SCANCODE_RIGHT:
                right_pressed = false;
                break;
            case SDL_SCANCODE_Z:
                z_pressed = false;
                break;
            case SDL_SCANCODE_X:
                x_pressed = false;
                break;
            default:
                break;
        }
    }
}
void Sprite::jump(bool jump){
    jump_pressed = jump;
}
float Sprite::xCollision(){
  float left = x_pos;
  float right = x_pos + SIZEX;
  float top = y_pos;
  float bottom = y_pos + SIZEY;
  for (unsigned int y = 0; y < Game::tilemap.size(); y++)
  {
    for (unsigned int x = 0; x < Game::tilemap[y].size(); x++)
    {
        if (Game::tilemap[y][x] == 1 && right + x_vel > x * Game::TILE_SIZE && right <= x * Game::TILE_SIZE+Game::TILE_SIZE*0.1 && bottom > y * Game::TILE_SIZE && top < y * Game::TILE_SIZE + Game::TILE_SIZE)
        {
          return x * Game::TILE_SIZE - SIZEX;
        }
        if (Game::tilemap[y][x] == 1 && left + x_vel < x * Game::TILE_SIZE + Game::TILE_SIZE && left >=  x * Game::TILE_SIZE+Game::TILE_SIZE*0.9 && bottom > y * Game::TILE_SIZE && top < y * Game::TILE_SIZE + Game::TILE_SIZE)
        {
          return x * Game::TILE_SIZE + Game::TILE_SIZE;
        }
    }
  }
  // for (unsigned int y = 0; y < Game::tilemap.size(); y++)
  // {
  //   for (unsigned int x = 0; x < Game::tilemap[y].size(); x++)
  //   {
  //     if (Game::tilemap[y][x] == 1 && right > x * Game::TILE_SIZE && left <= x * Game::TILE_SIZE && bottom > y * Game::TILE_SIZE && top < y * Game::TILE_SIZE + Game::TILE_SIZE)
  //     {
  //       return x * Game::TILE_SIZE - SIZEX;
  //     }
  //     if (Game::tilemap[y][x] == 1 && left < x * Game::TILE_SIZE + Game::TILE_SIZE && right >= x * Game::TILE_SIZE+Game::TILE_SIZE && bottom > y * Game::TILE_SIZE && top < y * Game::TILE_SIZE + Game::TILE_SIZE)
  //     {
  //       return x * Game::TILE_SIZE + Game::TILE_SIZE;
  //     }
  //   }
  // }
  return x_pos + x_vel;
}
float Sprite::yCollision(){
  float left = x_pos;
  float right = x_pos + SIZEX;
  float top = y_pos;
  float bottom = y_pos + SIZEY;
  for (unsigned int y = 0; y < Game::tilemap.size(); y++)
  {
    for (unsigned int x = 0; x < Game::tilemap[y].size(); x++){
        if (Game::tilemap[y][x] == 1 && bottom + y_vel > y * Game::TILE_SIZE && bottom <= y * Game::TILE_SIZE + Game::TILE_SIZE && right > x * Game::TILE_SIZE && left < x * Game::TILE_SIZE + Game::TILE_SIZE)
        {
          y_vel = 0;
          if(!can_jump){
            Mix_PlayChannel( -1, chunk1, 0 );
          }
          can_jump = true;
          return y * Game::TILE_SIZE - SIZEY;
        }
        if (Game::tilemap[y][x] == 1 && top + y_vel < y * Game::TILE_SIZE + Game::TILE_SIZE && top >= y * Game::TILE_SIZE && right > x * Game::TILE_SIZE && left < x * Game::TILE_SIZE + Game::TILE_SIZE)
        {
          y_vel = 0;
          return y * Game::TILE_SIZE + Game::TILE_SIZE;
        }
    }
  }
  return y_pos + y_vel;
}
void Sprite::windowCollision(){
  if (x_pos <= 0)
    x_pos = 0;
  if (x_pos >= Game::mWidth - SIZEX)
    x_pos = Game::mWidth - SIZEX;
  if (y_pos <= 0)
    y_pos = 0;
  if (y_pos >= Game::mHeight - SIZEY)
  {
    y_vel = 0;
    y_pos = Game::mHeight - SIZEY;
    if(!can_jump){
      Mix_PlayChannel( -1, chunk1, 0 );
    }
    can_jump = true;
  }
}
void Sprite::update(){
    float resize = (z_pressed-x_pressed);
    SIZEX += resize;
    rect.w += resize;
    rect2.w += resize;
    x_vel = (right_pressed - left_pressed)*SPEED;
    y_vel += GRAVITY;
    if (jump_pressed && can_jump){
        y_vel = JUMP;
        can_jump = false;
    }
    rect2.x = x_pos + x_vel;
    rect2.y = y_pos + y_vel;
    x_pos = xCollision();
    y_pos = yCollision();
    windowCollision();
    rect.x = x_pos;
    rect.y = y_pos;
}
int Sprite::getX(){
  return (int) (x_pos + 0.5*SIZEY);
}
int Sprite::getY(){
  return (int) (y_pos + 0.5*SIZEX);
}
void Sprite::render(SDL_Renderer* renderer){
    if (can_jump){
      SDL_RenderCopyF(renderer, image1, NULL, &rect);
    }
    if (!can_jump){
      SDL_RenderCopyF(renderer, image2, NULL, &rect);
    };
}
void Sprite::render2(SDL_Renderer* renderer){
  SDL_RenderCopyF(renderer, image3, NULL, &rect2);
};