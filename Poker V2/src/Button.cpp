#include "UI/Button.h"

Button::Button(SDL_Renderer* renderer, int x, int y, int w, int h, const std::string& text, TTF_Font* font)
    :renderer(renderer), text(text), font(font), textTexture(nullptr), color({200, 200, 200, 255}), textColor({0, 0, 0, 255}) {
    rect = {x, y, w, h};

    // Create the text texture
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    if (textSurface) {
        textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_FreeSurface(textSurface);
    } else {
        SDL_Log("Failed to create text surface: %s", TTF_GetError());
    }
}

Button::~Button() {
    if (textTexture) {
        SDL_DestroyTexture(textTexture);
    }
}

void Button::render() {
    // Render the button rectangle
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);

    // Render the button outline
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black outline
    SDL_RenderDrawRect(renderer, &rect);

    // Render the text in the center of the button
    if (textTexture) {
        int textWidth, textHeight;
        SDL_QueryTexture(textTexture, nullptr, nullptr, &textWidth, &textHeight);
        SDL_Rect textRect = {rect.x + (rect.w - textWidth) / 2, rect.y + (rect.h - textHeight) / 2, textWidth, textHeight};
        SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
    }
}

bool Button::isClicked(int mouseX, int mouseY) {
    return (mouseX >= rect.x && mouseX <= rect.x + rect.w && mouseY >= rect.y && mouseY <= rect.y + rect.h);
}
