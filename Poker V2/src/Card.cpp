#include "Core/Card.h"

Card::Card(SDL_Renderer* ren, int x, int y, Suit cardSuit, Rank cardRank) {
    renderer = ren;
    cardTexture = TextureManager::LoadTexture(textureSheet, ren);

    suit = cardSuit;
    rank = cardRank;
    
    xPos = x;
    yPos = y;
};

Card::~Card() {
    if (cardTexture) {               // Check if the texture exists
        SDL_DestroyTexture(cardTexture); // Free the texture
        cardTexture = nullptr;       // Nullify the pointer for safety
    }
}


void Card::update(int x, int y) {
    xPos = x;
    yPos = y;
    srcRect = {(rank - 2) * width , suit * height, width, height};
    destRect = {xPos, yPos, static_cast<int>(width * 0.5), static_cast<int>(height * 0.5)};
}
void Card::render() {
    SDL_RenderCopy(renderer, cardTexture, &srcRect, &destRect);
}