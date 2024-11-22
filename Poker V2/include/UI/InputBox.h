#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <string>

class InputBox {
public:
    // Constructor: x, y for position; width, height for size; font for text; renderer for rendering.
    InputBox(int x, int y, int width, int height, TTF_Font* font, SDL_Renderer* renderer);

    // Destructor to free allocated memory
    ~InputBox();

    // Renders the input box and its content (text and cursor)
    void render();

    // Handles events (clicks and key presses)
    void handleEvents(SDL_Event& event, std::string & input);

    // Returns the current text in the input box
    std::string getText() const;

private:
    // Box dimensions
    SDL_Rect boxRect; 
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Texture* textTexture;  // Holds the texture of the typed text
    std::string text;          // Stores the input text
    SDL_Color textColor;       // Text color
    bool isActive;             // Tracks if the input box is active (clicked)
    int cursorPosition;       // To track the text cursor position

    // Updates the text texture with the current input text
    void updateTextTexture();
};
