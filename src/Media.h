#pragma once

#include "Game.h"

class Media
{
private:
    std::map<std::string, SDL_Texture*> textures;
    std::map<std::string, Mix_Chunk*> sounds;
public:
    Media();
    ~Media();
	SDL_Texture* loadTexture(const char* fileName);
    Mix_Chunk* loadSound(const char* fileName);
	void addTexture(std::string id, const char* fileName);
	void addSound(std::string id, const char* fileName);
	SDL_Texture* getTexture(std::string id);
	Mix_Chunk* getSound(std::string id);
    vector<vector<int>> loadTilemap(const char* fileName);
    void clear();
};