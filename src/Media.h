#pragma once

#include "Game.h"
class Media
{
public:
    Media();
    ~Media();
	static SDL_Texture* loadTexture(const char* fileName,SDL_Renderer* renderer);
    static Mix_Chunk* loadSound(const char* fileName);
    static Mix_Music* loadMusic(const char* fileName);
    static std::vector<std::vector<int>> loadTilemap(const char* fileName);
    void clear();
};