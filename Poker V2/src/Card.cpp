#include "Card.h"

Card::Card(SDL_Renderer* ren, int x, int y, Suit cardSuit, Rank cardRank) {
    renderer = ren;
    cardTexture = TextureManager::LoadTexture(textureSheet, ren);

    suit = cardSuit;
    rank = cardRank;
    
    xPos = x;
    yPos = y;
};

Card::~Card() {

}

void Card::update() {
    srcRect = {(rank - 2) * width , suit * height, width, height};
    destRect = {xPos, yPos, width, height};
}
void Card::render() {
    SDL_RenderCopy(renderer, cardTexture, &srcRect, &destRect);
}