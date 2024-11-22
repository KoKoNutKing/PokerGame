#pragma once

#include "Core/Game.h"
#include "Core/TextureManager.h"
#include <string>

const std::string SUITS[4] = {"Clubs", "Diamonds", "Hearts", "Spades"};
const std::string RANKS[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};

// Enum for suit and rank types
enum Suit { HEARTS, SPADES, DIAMONDS, CLUBS };
enum Rank { TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };

// Structure for Card
class Card {
public:
    Card(SDL_Renderer* ren, int x, int y, Suit cardSuit, Rank cardRank);
    Card();  
    ~Card();
    
    Rank rank;
    Suit suit;

    void update(int x, int y);
    void render();
private:
    const char* textureSheet = "resrc\\CardsSprite.png";

    int xPos, yPos;
    int width = 225, height = 315;
    float scale;

    SDL_Texture* cardTexture;
    SDL_Rect srcRect, destRect;
    SDL_Renderer* renderer;

    // Display card
    //void displayCard() const;
};
