#pragma once

#include <random>
#include <algorithm>

#include "Card.h"

class Deck {
public:
    void createDeck();
    void shuffleDeck();

private:
    Card cards[52];
    
};

