#include <stdio.h>
#include <iostream>
#include <stdbool.h>
#include <SDL2/SDL.h>
int mWidth =640;
int mHeight= 200;
const int SIZE =100;
const int SPEED= 600;
const int GRAVITY =60;
const int FPS = 60;
const int JUMP = -1200;

int main(int argc, char* argv[])
{
	/* Initializes the timer, audio, video, joystick,
  haptic, gamecontroller and events subsystems */
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    printf("Error initializing SDL: %s\n", SDL_GetError());
    return 0;
  }
  /* Create a window */
  SDL_Window* window = SDL_CreateWindow("Hello Platformer!",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,mWidth, mHeight, SDL_WINDOW_RESIZABLE);
  if (!window)
  {
    printf("Error creating window: %s\n", SDL_GetError());
    SDL_Quit();
    return 0;
  }
  /* Create a renderer */
  Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
  SDL_Renderer* rend = SDL_CreateRenderer(window, -1, render_flags);
  if (!rend)
  {
    printf("Error creating renderer: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
  }
  /* Main loop */
  bool running = true, jump_pressed = false, can_jump = true,
                  left_pressed = false, right_pressed = false;
  float x_pos = (mWidth-SIZE)/2, y_pos = (mHeight-SIZE)/2, x_vel = 0, y_vel = 0;
  SDL_Rect rect = {(int) x_pos, (int) y_pos, SIZE, SIZE};
  SDL_Event event;
  while (running)
  {
    /* Process events */
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
        case SDL_QUIT:
          running = false;
          break;
        case SDL_WINDOWEVENT:
          if (event.window.event == SDL_WINDOWEVENT_RESIZED)
          {
            mWidth = event.window.data1;
            mHeight = event.window.data2;
            printf("GRAAAH");
          }
          break;
        case SDL_KEYDOWN:
          switch (event.key.keysym.scancode)
          {
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
            default:
              break;
           }
          break;
        case SDL_KEYUP:
          switch (event.key.keysym.scancode)
          {
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
          break;
        default:
          break;
      }
    }
    /* Clear screen */
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderClear(rend);
    /* Move the rectangle */
    x_vel = (right_pressed - left_pressed)*SPEED;
    y_vel += GRAVITY;
    if (jump_pressed && can_jump)
    {
      can_jump = false;
      y_vel = JUMP;
    }
    x_pos += x_vel / 60;
    y_pos += y_vel / 60;
    if (x_pos <= 0)
      x_pos = 0;
    if (x_pos >= mWidth - rect.w)
      x_pos = mWidth - rect.w;
    if (y_pos <= 0)
      y_pos = 0;
    if (y_pos >= mHeight - rect.h)
    {
      y_vel = 0;
      y_pos = mHeight - rect.h;
      if (!jump_pressed)
        can_jump = true;
    }
    rect.x = (int) x_pos;
    rect.y = (int) y_pos;
    /* Draw the rectangle */
    SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
    SDL_RenderFillRect(rend, &rect);
    /* Draw to window and loop */
    SDL_RenderPresent(rend);
    SDL_Delay(1000/FPS);
  }
  /* Release resources */
  SDL_DestroyRenderer(rend);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}