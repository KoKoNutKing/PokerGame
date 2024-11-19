#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <string>

class Button {
public:
    Button(SDL_Renderer* renderer, int x, int y, int w, int h, const std::string& text, TTF_Font* font);
    ~Button();

    void render(SDL_Renderer* renderer);
    bool isClicked(int mouseX, int mouseY);

private:
    SDL_Rect rect;               // Button rectangle
    SDL_Color color;             // Button color
    SDL_Color textColor;         // Text color
    std::string text;            // Button text
    SDL_Texture* textTexture;    // Text texture
    TTF_Font* font;              // Font for text
};
