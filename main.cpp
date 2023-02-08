#include <stdio.h>
#include <iostream>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
int mWidth =640;
int mHeight= 200;
int SIZEX = 100;
int SIZEY = 200;
const int SPEED= 600;
const int GRAVITY =60;
const int FPS = 60;
const int JUMP = -1200;
using namespace std;

int throw_sdl_err(const char* fmt)
{
    SDL_LogError(
        SDL_LOG_CATEGORY_APPLICATION,
        fmt,
        SDL_GetError()
    );
    return 3; // constant error code.
}
int main(int argc, char* argv[])
{
  SDL_Window*     window;
  SDL_Renderer*   renderer;
  SDL_Surface*    surface1;
  SDL_Surface*    surface2;
  SDL_Texture*    texture1;
  SDL_Texture*    texture2;
  SDL_Event       event;
  Mix_Chunk* sound;

  // Check load
	/* Initializes the timer, audio, video, joystick,
  haptic, gamecontroller and events subsystems */

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    return throw_sdl_err("Error initializing SDL: %s\n");
  }

	if ( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 1024 ) < 0 ) {
		cout << "Error initializing SDL_mixer: " << Mix_GetError() << endl;
		return false;
	}

  /* Create a window */
  window = SDL_CreateWindow("Hello Platformer!",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,mWidth, mHeight, SDL_WINDOW_RESIZABLE);
  if (!window)
  {
    SDL_Quit();
    return throw_sdl_err("Error creating window: %s\n");
    SDL_Quit();
  }

  /* Create a renderer */
  Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
  renderer = SDL_CreateRenderer(window, -1, render_flags);
  if (!renderer)
  {
    SDL_DestroyWindow(window);
    SDL_Quit();
    return throw_sdl_err("Error creating renderer: %s\n");
  }
  
  /* Main loop */
  bool running = true, jump_pressed = false, can_jump = true,
                  left_pressed = false, right_pressed = false;

  float x_pos = (mWidth-SIZEX)/2, y_pos = (mHeight-SIZEY)/2, x_vel = 0, y_vel = 0;

  SDL_Rect rect = {(int) x_pos, (int) y_pos, SIZEX, SIZEY};

  surface1 = SDL_LoadBMP("C:/Developement/Projects/Tutorial/MyMan.bmp" );
  if (!surface1) {
      return throw_sdl_err("Could not load BMP image: %s");
  }
  surface2 = SDL_LoadBMP("C:/Developement/Projects/Tutorial/Hate.bmp" );
  if (!surface2) {
      return throw_sdl_err("Could not load BMP image: %s");
  }

  texture1 = SDL_CreateTextureFromSurface(renderer, surface1);
  if (!texture1) {
      return throw_sdl_err("Could not create new texture from surface: %s");
  }

  SDL_FreeSurface(surface1);

  texture2 = SDL_CreateTextureFromSurface(renderer, surface2);
  if (!texture2) {
      return throw_sdl_err("Could not create new texture from surface: %s");
  }

  SDL_FreeSurface(surface2);

  sound = Mix_LoadWAV("C:/Developement/Projects/Tutorial/DING.mp3");
  if(!sound ) {
    cout << "Failed to load music or sound: " << Mix_GetError() << endl;
  }

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
            case SDL_SCANCODE_Z:
              SIZEX -= 1;
              rect.w -= 1;
              break;
            case SDL_SCANCODE_X:
              SIZEY -= 1;
              rect.h -= 1;
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
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_RenderClear(renderer);

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
      if(!can_jump){
				Mix_PlayChannel( -1, sound, 0 );
      }
      can_jump = true;
    }
    rect.x = (int) x_pos;
    rect.y = (int) y_pos;

    /* Draw the rectangle */
    if (can_jump){
      SDL_RenderCopy(renderer, texture1, NULL, &rect);
    }
    if (!can_jump){
      SDL_RenderCopy(renderer, texture2, NULL, &rect);
    };

    /* Draw to window and loop */
    SDL_RenderPresent(renderer);
    SDL_Delay(1000/FPS);
  }
  /* Release resources */
  SDL_DestroyTexture(texture1);
  SDL_DestroyTexture(texture2);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  Mix_FreeChunk( sound );
  Mix_Quit();
  return 0;
}