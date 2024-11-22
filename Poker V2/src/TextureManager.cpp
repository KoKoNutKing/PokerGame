#include "Core/TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* filename, SDL_Renderer* rendererer) {
    SDL_Surface* tmpSurface = IMG_Load(filename);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(rendererer, tmpSurface);
    SDL_FreeSurface(tmpSurface);

    return texture;
}