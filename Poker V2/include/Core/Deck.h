#pragma once

#include "Core/Card.h"  // Include full definition of Card class
#include <algorithm>

class Deck {
public:
    Deck(SDL_Renderer* ren);  // Constructor
    void createDeck();
    void shuffleDeck();

private:
    SDL_Renderer* renderer;  // Pointer to SDL_Renderer
    Card* cards[52];  // An array of 52 pointers to Card objects
    int currentIndex = 0;  // To track the current position in the deck
};
