#pragma once

#include "Core/Card.h"  // Include the Card class for Suit and Rank

class Deck {
public:
    Deck(SDL_Renderer* ren);
    ~Deck();  // Destructor to clean up allocated memory
    void createDeck();
    void shuffleDeck();
    Card* drawCard(int index);

    void checkDeck() const;  // Make this method const for read-only checks

private:
    SDL_Renderer* renderer;  // For rendering cards
    Card* cards[52];         // Array of pointers to Card objects
    int currentIndex = 0;    // Current index for drawing cards
};
