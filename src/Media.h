#pragma once

#include "Game.h"

class Media
{
private:
    std::map<std::string, int*> textures;
public:
    Media();
    ~Media();
	SDL_Texture* loadTexture(const char* fileName);
};