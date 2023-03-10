#include "Sprite.h"

Sprite::Sprite(float x, float y, int sizex, int sizey, SDL_Renderer* renderer)
{
  this->x_pos = x;
  this->renderer = renderer;
  this->y_pos = y;
  this->image1 = Media::loadTexture("images/Face1rizz.png",renderer);
  this->image2 = Media::loadTexture("images/Face2.png",renderer);
  this->image3 = Media::loadTexture("images/Face3.png",renderer);
  this->chunk1 = Media::loadSound("sounds/DING.mp3");
  this->SIZEX = sizex;
  this->SIZEY = sizey;
  rect = {(int) x_pos, (int) y_pos, SIZEX, SIZEY};
  rect2 = {(int) x_ppos, (int) y_ppos, SIZEX, SIZEY};
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
                SIZEX -= 1;
                rect.w -= 1;
                break;
            case SDL_SCANCODE_X:
                SIZEX += 1;
                rect.w += 1;
                break;
            default:
                break;
        }
    }
    if (Game::event.type == SDL_KEYUP){
        switch (Game::event.key.keysym.scancode){
            case SDL_SCANCODE_SPACE:
                jump_pressed = false;
                break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_LEFT:
                left_pressed = false;
                break;
            case SDL_SCANCODE_D:
            case SDL_SCANCODE_RIGHT:
                right_pressed = false;
                break;
            default:
                break;
        }
    }
}
void Sprite::jump(bool jump){
    jump_pressed = jump;
}
void Sprite::update(){
    left = x_pos;
    right = x_pos + SIZEX;
    top = y_pos;
    bottom = y_pos + SIZEY;
    x_vel = (right_pressed - left_pressed)*SPEED;
    y_vel += GRAVITY;
    printf("%f     ",y_vel);
    if (jump_pressed && can_jump){
        y_vel = JUMP;
        can_jump = false;
    }
    x_ppos = x_pos + x_vel;
    y_ppos = y_pos + y_vel;
    rect2.x = x_ppos;
    rect2.y = y_ppos;
    for (int y = 0; y < Game::tilemap.size(); y++)
    {
      for (int x = 0; x < Game::tilemap[y].size(); x++)
      {
        if(x_vel>0){
          if (Game::tilemap[y][x] == 1 && right + x_vel > x * TILE_SIZE && right <= x * TILE_SIZE && bottom > y * TILE_SIZE && top < y * TILE_SIZE + TILE_SIZE)
          {
            x_ppos = x * TILE_SIZE - SIZEX;
          }
        }
        else if(x_vel<0){
          if (Game::tilemap[y][x] == 1 && left + x_vel < x * TILE_SIZE + TILE_SIZE && left >= x * TILE_SIZE + TILE_SIZE && bottom > y * TILE_SIZE && top < y * TILE_SIZE + TILE_SIZE)
          {
            x_ppos = x * TILE_SIZE + TILE_SIZE;
          }
        }
      }
    }
    x_pos = x_ppos;
    left = x_pos;
    right = x_pos + SIZEX;
    for (int y = 0; y < Game::tilemap.size(); y++)
    {
      for (int x = 0; x < Game::tilemap[y].size(); x++)
      {
        if(y_vel>0){
          if (Game::tilemap[y][x] == 1 && bottom + y_vel > y * TILE_SIZE && bottom <= y * TILE_SIZE && right > x * TILE_SIZE && left < x * TILE_SIZE + TILE_SIZE)
          {
            y_vel = 0;
            y_ppos = y * TILE_SIZE - SIZEY;
            if(!can_jump){
              Mix_PlayChannel( -1, chunk1, 0 );
            }
            can_jump = true;
          }
        }
        else if(y_vel<0){
          if (Game::tilemap[y][x] == 1 && top + y_vel < y * TILE_SIZE + TILE_SIZE && top >= y * TILE_SIZE + TILE_SIZE && right > x * TILE_SIZE && left < x * TILE_SIZE + TILE_SIZE)
          {
            y_ppos = y * TILE_SIZE + TILE_SIZE;
          }
        }
      }
    }
    y_pos = y_ppos;
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
    rect.x = (int) x_pos;
    rect.y = (int) y_pos;
}
void Sprite::render(SDL_Renderer* renderer){
    if (can_jump){
      SDL_RenderCopy(renderer, image1, NULL, &rect);
    }
    if (!can_jump){
      SDL_RenderCopy(renderer, image2, NULL, &rect);
    };
}
void Sprite::render2(SDL_Renderer* renderer){
  SDL_RenderCopy(renderer, image3, NULL, &rect2);
};