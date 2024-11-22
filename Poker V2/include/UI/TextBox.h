#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <string>

class TextBox {
public:
    // Constructor to initialize the TextBox
    TextBox(int x, int y, int w, int h, TTF_Font* font, SDL_Renderer* renderer);
    
    // Destructor to clean up resources
    ~TextBox();
    
    // Render the TextBox (draw the box and the text inside)
    void render();
    
    // Set the text in the TextBox
    void setText(const std::string& newText);
    
    // Get the current text from the TextBox
    std::string getText() const;

private:
    int x, y, w, h;  // Position and size of the text box
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Color textColor;
    SDL_Texture* textTexture;  // Texture to hold the rendered text
    SDL_Rect textRect;  // The rectangle for the text position
    
    std::string text;  // The current text in the TextBox
};
