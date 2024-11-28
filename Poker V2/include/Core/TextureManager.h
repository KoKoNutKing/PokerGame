#pragma once

#include "Core/Game.h"

class TextureManager {
public:
    static SDL_Texture* LoadTexture(const char* filename, SDL_Renderer* renderer);
    
    static void DrawTexture(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Rect srcRect, SDL_Rect destRect);
};