#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <string>

class InputBox {
public:
    InputBox(int x, int y, int width, int height, TTF_Font* font, SDL_Renderer* renderer);

    ~InputBox();

    void render();

    void handleEvents(SDL_Event& event);

    std::string getText() const;

private:
    // Box dimensions
    SDL_Renderer* renderer;
    SDL_Rect boxRect; 
    SDL_Color textColor;       // Text color
    SDL_Texture* textTexture;  // Holds the texture of the typed text
    std::string text;          // Stores the input text
    TTF_Font* font;
    bool isActive;             // Tracks if the input box is active (clicked)
    int cursorPosition;       // To track the text cursor position

    // Updates the text texture with the current input text
    void updateTextTexture();
};
