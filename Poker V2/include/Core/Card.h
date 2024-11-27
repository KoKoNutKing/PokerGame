#pragma once

#include "Core/Game.h"
#include "Core/TextureManager.h"

#include "Core/Config.h"


// Enum for suit and rank types
enum Suit { HEARTS, SPADES, DIAMONDS, CLUBS };
enum Rank { TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };

// Structure for Card
class Card {
public:
    Card(SDL_Renderer* ren, int x, int y, Suit cardSuit, Rank cardRank);
    ~Card();
    
    Rank rank;
    Suit suit;

    void update(int x, int y);
    void render();
private:
    const char* textureSheet = Config::FaceUpCard;

    int xPos, yPos;
    int width = Config::CardWidth, height = Config::CardHeight;
    float scale;

    SDL_Texture* cardTexture;
    SDL_Rect srcRect, destRect;
    SDL_Renderer* renderer;

    // Display card
    //void displayCard() const;
};
