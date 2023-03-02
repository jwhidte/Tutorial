#include "Media.h"

SDL_Texture* Media::loadTexture(const char* source){
    SDL_Surface* temporarySurface = IMG_Load(source);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, temporarySurface);
    SDL_FreeSurface(temporarySurface);
    return texture;
}