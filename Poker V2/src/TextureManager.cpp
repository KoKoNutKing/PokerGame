#include "Core/TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* filename, SDL_Renderer* rendererer) {
    SDL_Surface* tmpSurface = IMG_Load(filename);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(rendererer, tmpSurface);
    SDL_FreeSurface(tmpSurface);

    return texture;
}

void TextureManager::DrawTexture(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Rect srcRect, SDL_Rect destRect) {
    if (!texture) {
        std::cerr << "Cannot draw texture: texture is null!" << std::endl;
        return;
    }
    SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
}