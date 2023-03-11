#include "Media.h"
Media::Media()
{}

Media::~Media()
{}
SDL_Texture* Media::loadTexture(const char* source,SDL_Renderer* renderer){
    SDL_Surface* temporarySurface = IMG_Load(source);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, temporarySurface);
    SDL_FreeSurface(temporarySurface);
    return texture;
}
Mix_Chunk* Media::loadSound(const char* source){
    Mix_Chunk* sound = Mix_LoadWAV(source);
    sound = Mix_LoadWAV("sounds/DING.mp3");
    return sound;
}
std::vector<std::vector<int>> Media::loadTilemap(const char* fileName){
    std::vector<std::vector<int>> tilemap;
    int mapWidth, mapHeight;
    FILE* fp = fopen(fileName, "r");
    if (!fp)
    {
        std::cout << "Failed to open tilemap file!" << std::endl;
        return tilemap;
    }
    fscanf(fp, "%d %d", &mapWidth, &mapHeight);
    tilemap.resize(mapHeight, std::vector<int>(mapWidth));
    for (int y = 0; y < mapHeight; y++)
    {
        for (int x = 0; x < mapWidth; x++)
        {
            fscanf(fp, "%d", &tilemap[y][x]);
        }
    }
    fclose(fp);
    return tilemap;
}