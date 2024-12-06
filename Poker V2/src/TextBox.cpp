#include "UI/TextBox.h"
#include <iostream>

// Constructor to initialize the TextBox
TextBox::TextBox(int x, int y, int w, int h, TTF_Font* font, SDL_Renderer* renderer)
    : font(font), renderer(renderer), text("") {
    textColor = { 255, 255, 255, 255 };  // White color for text
    textTexture = nullptr;
    textRect = { x, y, w, h };
}

// Destructor to clean up resources
TextBox::~TextBox() {
    if (textTexture) {
        SDL_DestroyTexture(textTexture);
    }
}


void TextBox::render() {

    // Render the text inside the TextBox
    if (!text.empty()) {
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
        if (textSurface) {
            textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            SDL_FreeSurface(textSurface);

            SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);  // Update the text rect with the size
            SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
        }
    }
}

// Set the text in the TextBox
void TextBox::setText(const std::string& newText) {
    text = newText;
}

// Get the current text from the TextBox
std::string TextBox::getText() const {
    return text;
}
