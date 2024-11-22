#include "Core/Card.h"

Card::Card(SDL_Renderer* ren, int x, int y, Suit cardSuit, Rank cardRank) {
    renderer = ren;
    cardTexture = TextureManager::LoadTexture(textureSheet, ren);

    suit = cardSuit;
    rank = cardRank;
    
    xPos = x;
    yPos = y;
};

Card::Card() : renderer(nullptr), cardTexture(nullptr), suit(CLUBS), rank(TWO), xPos(0), yPos(0), width(225), height(315) {
    // Default constructor initializes with default values
}

Card::~Card() {

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