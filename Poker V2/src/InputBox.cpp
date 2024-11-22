#include "UI/InputBox.h"
#include <iostream>

InputBox::InputBox(int x, int y, int width, int height, TTF_Font* font, SDL_Renderer* renderer)
    : font(font), renderer(renderer), isActive(false), cursorPosition(0), text("") {
    // Set the position and size of the input box
    boxRect = { x, y, width, height };

    // Set the text color (black)
    textColor = { 255, 0, 0, 255 };

    // Initialize textTexture to null
    textTexture = nullptr;
}

InputBox::~InputBox() {
    if (textTexture != nullptr) {
        SDL_DestroyTexture(textTexture); // Clean up the texture
    }
}

void InputBox::render() {
    // Draw the input box outline (light gray)
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderDrawRect(renderer, &boxRect);

    // Render the text inside the input box
    if (textTexture != nullptr) {
        int w, h;
        SDL_QueryTexture(textTexture, nullptr, nullptr, &w, &h);
        SDL_Rect dstRect = { boxRect.x + 5, boxRect.y + (boxRect.h - h) / 2, w, h };
        SDL_RenderCopy(renderer, textTexture, nullptr, &dstRect);
    }

    // If the box is active, draw a blinking cursor at the end of the text
    if (isActive) {
        int textWidth = 0;
        TTF_SizeText(font, text.c_str(), &textWidth, nullptr); // Get the width of the text
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Black cursor
        SDL_RenderDrawLine(renderer, boxRect.x + 5 + textWidth, boxRect.y + 5, boxRect.x + 5 + textWidth, boxRect.y + boxRect.h - 5);
    }
}

void InputBox::handleEvents(SDL_Event& event, std::string & input) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        // Check if the click is inside the input box
        int mouseX = event.button.x;
        int mouseY = event.button.y;
        if (mouseX > boxRect.x && mouseX < boxRect.x + boxRect.w && mouseY > boxRect.y && mouseY < boxRect.y + boxRect.h) {
            isActive = true;  // Activate the input box when clicked
        } else {
            isActive = false;  // Deactivate the input box if clicked outside
        }
    }

    // Handle key events (typing)
    if (event.type == SDL_KEYDOWN && isActive) {
        if (event.key.keysym.sym == SDLK_BACKSPACE && !text.empty()) {
            // Remove the last character when backspace is pressed
            text.pop_back();
        } else if (event.key.keysym.sym == SDLK_RETURN) {
            // Submit the text when Enter is pressed

            //std::cout << "Entered Text: " << text << std::endl;
            input = text;
            isActive = false;  // Optionally deactivate after pressing enter

        } else if (event.key.keysym.sym >= SDLK_SPACE && event.key.keysym.sym <= SDLK_z) {
            // Add a character to the text (from space to z for simplicity)
            text += static_cast<char>(event.key.keysym.sym);
        }
    }

    // Update the texture for the typed text
    updateTextTexture();
}

std::string InputBox::getText() const {
    return text;  // Return the typed text
}

void InputBox::updateTextTexture() {
    // Destroy the old texture
    if (textTexture != nullptr) {
        SDL_DestroyTexture(textTexture);
    }

    // Create a new texture from the current text
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    if (textSurface != nullptr) {
        textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_FreeSurface(textSurface);  // Free the surface after creating the texture
    } else {
        std::cerr << "Failed to create text surface: " << TTF_GetError() << std::endl;
    }
}
