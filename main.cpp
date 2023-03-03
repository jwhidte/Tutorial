#include "Sprite.h"

using std::vector;

int mWidth =640;
int mHeight= 200;

int SIZEX = 64, SIZEY = 64;
//SDL Variables
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
// Tilemap variables
vector<vector<int>> tilemap;
int mapWidth, mapHeight;
SDL_Texture* tileTexture = nullptr;
SDL_Texture*    texture1 = nullptr;
SDL_Texture*    texture2 = nullptr;
Mix_Chunk*         sound = nullptr;
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
int init(){
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    return throw_sdl_err("Error initializing SDL: %s\n");
  }

	if (Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 1024 ) < 0 ) 
  {
		cout << "Error initializing SDL_mixer: " << Mix_GetError() << endl;
		return 3;
	}

  if (!IMG_Init(IMG_INIT_PNG))
  {
    cout << "Error initializing SDL_IMG: " << IMG_GetError() << endl;
    return 3;
  }
  /* Create a window */
  window = SDL_CreateWindow("Hello Platformer!",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,mWidth, mHeight, SDL_WINDOW_RESIZABLE);
  if (!window)
  {
    return throw_sdl_err("Error creating window: %s\n");
  }

  /* Create a renderer */
  Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
  renderer = SDL_CreateRenderer(window, -1, render_flags);
  if (!renderer)
  {
    SDL_DestroyWindow(window);
    return throw_sdl_err("Error creating renderer: %s\n");
  }
  return 0;
}
int loadMedia()
{
  // Load tile texture
  SDL_Surface* tileSurface = IMG_Load("images\\tile.png");
  if (!tileSurface)
  {
    return throw_sdl_err("Failed to load tile texture: %s\n");
  }



  tileTexture = SDL_CreateTextureFromSurface(renderer, tileSurface);
  if (!tileTexture)
  {
    return throw_sdl_err("Failed to create tile texture: %s\n");
  }



  // Load tilemap
  FILE* fp = fopen("images/tilemap.txt", "r");
  if (!fp)
  {
    cout << "Failed to open tilemap file!" << endl;
    return 3;
  }


  fscanf(fp, "%d %d", &mapWidth, &mapHeight);
  tilemap.resize(mapHeight, vector<int>(mapWidth));
  for (int y = 0; y < mapHeight; y++)
  {
    for (int x = 0; x < mapWidth; x++)
    {
      fscanf(fp, "%d", &tilemap[y][x]);
    }
  }
  fclose(fp);
// Load images

  SDL_Surface*    surface1;
  SDL_Surface*    surface2;

  surface1 = SDL_LoadBMP("images/MyMan.bmp" );
  if (!surface1) {
    return throw_sdl_err("Could not load BMP image: %s");
  }
  surface2 = SDL_LoadBMP("images/Hate.bmp" );
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

  sound = Mix_LoadWAV("sounds/DING.mp3");
  if(!sound ) {
    cout << "Failed to load music or sound: " << Mix_GetError() << endl;
    return 3;
  }

  return 0;
}
int xCollision(int xpos, int ypos, int xvel, int sizeX, int sizeY){
  for (int y = 0; y < tilemap.size(); y++)
  {
    for (int x = 0; x < tilemap[y].size(); x++)
    {
      if(xvel>0){
        if (tilemap[y][x] == 1 && xpos + sizeX + xvel/FPS > x * TILE_SIZE && xpos + sizeX <= x * TILE_SIZE && ypos + sizeY > y * TILE_SIZE && ypos < y * TILE_SIZE + TILE_SIZE)
        {
          return x * TILE_SIZE - sizeX;
        }
      }
      else if(xvel<0){
        if (tilemap[y][x] == 1 && xpos + xvel/FPS < x * TILE_SIZE + TILE_SIZE && xpos >= x * TILE_SIZE + TILE_SIZE && ypos + sizeY > y * TILE_SIZE && ypos < y * TILE_SIZE + TILE_SIZE)
        {
          return x * TILE_SIZE + TILE_SIZE;
        }
      }
    }
  }
  return xpos+xvel/FPS;
}
int yCollision(int xpos, int ypos, int yvel, int sizeX, int sizeY){
  for (int y = 0; y < tilemap.size(); y++)
  {
    for (int x = 0; x < tilemap[y].size(); x++)
    {
      if(yvel>0){
        if (tilemap[y][x] == 1 && ypos + sizeY + yvel/FPS > y * TILE_SIZE && ypos + sizeY <= y * TILE_SIZE && xpos + sizeX > x * TILE_SIZE && xpos < x * TILE_SIZE + TILE_SIZE)
        {
          return y * TILE_SIZE - sizeY;
        }
      }
      else if(yvel<0){
        if (tilemap[y][x] == 1 && ypos + yvel/FPS < y * TILE_SIZE + TILE_SIZE && ypos >= y * TILE_SIZE + TILE_SIZE && xpos + sizeX > x * TILE_SIZE && xpos < x * TILE_SIZE + TILE_SIZE)
        {
          return y * TILE_SIZE + TILE_SIZE;
        }
      }
    }
  }
  return ypos+yvel/FPS;
}
int main(int argc, char** args)
{
  printf(SDL_GetBasePath());
    if (init())
    {
        cout << "Failed to initialize!" << endl;
        return 1;
    }

    // Load game resources
    if (loadMedia())
    {
        cout << "Failed to load media!" << endl;
        return 1;
    }

  SDL_Event  event;
  // Check load
	/* Initializes the timer, audio, video, joystick,
  haptic, gamecontroller and events subsystems */

  
  /* Main loop */
  bool running = true, jump_pressed = false, can_jump = true, left_pressed = false, right_pressed = false;

  float x_pos = (mWidth-SIZEX)/2, y_pos = (mHeight-SIZEY)/2, x_vel = 0, y_vel = 0, x_ppos = 0, y_ppos = 0;

  SDL_Rect rect = {(int) x_pos, (int) y_pos, SIZEX, SIZEY};

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
              SIZEX += 1;
              rect.w += 1;
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
    y_vel += GRAVITY/FPS;
    if (jump_pressed && can_jump)
    {
      can_jump = false;
      y_vel = JUMP;
    }
    x_ppos = x_pos + x_vel/FPS;
    y_ppos = y_pos + y_vel/FPS;
    for (int y = 0; y < tilemap.size(); y++)
    {
      for (int x = 0; x < tilemap[y].size(); x++)
      {
        if(x_vel>0){
          if (tilemap[y][x] == 1 && x_pos + SIZEX + x_vel/FPS > x * TILE_SIZE && x_pos + SIZEX <= x * TILE_SIZE && y_pos + SIZEY > y * TILE_SIZE && y_pos < y * TILE_SIZE + TILE_SIZE)
          {
            x_ppos = x * TILE_SIZE - SIZEX;
          }
        }
        else if(x_vel<0){
          if (tilemap[y][x] == 1 && x_pos + x_vel/FPS < x * TILE_SIZE + TILE_SIZE && x_pos >= x * TILE_SIZE + TILE_SIZE && y_pos + SIZEY > y * TILE_SIZE && y_pos < y * TILE_SIZE + TILE_SIZE)
          {
            x_ppos = x * TILE_SIZE + TILE_SIZE;
          }
        }
      }
    }
    x_pos = x_ppos;
    for (int y = 0; y < tilemap.size(); y++)
    {
      for (int x = 0; x < tilemap[y].size(); x++)
      {
        if(y_vel>0){
          if (tilemap[y][x] == 1 && y_pos + SIZEY + y_vel/FPS > y * TILE_SIZE && y_pos + SIZEY <= y * TILE_SIZE && x_pos + SIZEX > x * TILE_SIZE && x_pos < x * TILE_SIZE + TILE_SIZE)
          {
            y_ppos = y * TILE_SIZE - SIZEY;
            can_jump = true;
          }
        }
        else if(y_vel<0){
          if (tilemap[y][x] == 1 && y_pos + y_vel/FPS < y * TILE_SIZE + TILE_SIZE && y_pos >= y * TILE_SIZE + TILE_SIZE && x_pos + SIZEX > x * TILE_SIZE && x_pos < x * TILE_SIZE + TILE_SIZE)
          {
            y_ppos = y * TILE_SIZE + TILE_SIZE;
          }
        }
      }
    }
    y_pos = y_ppos;
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
    for (int y = 0; y < mapHeight; y++)
    {
        for (int x = 0; x < mapWidth; x++)
        {
            if (tilemap[y][x] == 1)
            {
                SDL_Rect tileRect = { x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
                SDL_RenderCopy(renderer, tileTexture, nullptr, &tileRect);
            }
        }
    }
    /* Draw to window and loop */
    SDL_RenderPresent(renderer);
    SDL_Delay(1000/FPS);
    printf("%d\n", rect.y);
  }
  /* Release resources */
  // Free loaded images
  SDL_DestroyTexture(tileTexture);
  tileTexture = nullptr;
  SDL_DestroyTexture(texture1);
  texture1 = nullptr;
  SDL_DestroyTexture(texture2);
  texture2 = nullptr;
  Mix_FreeChunk( sound );
  sound = nullptr;
  // Destroy window
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  renderer = nullptr;
  window = nullptr;

  // Quit SDL subsystems
  IMG_Quit();
  Mix_Quit();
  SDL_Quit();
  return 0;
}