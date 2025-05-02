#ifndef DECK_H
#define DECK_H

#include <random>
#include <algorithm>

#include "Card.h"

struct Deck {
    Card cards[52];

    void createDeck();
    void shuffleDeck();
    
};

#endif
