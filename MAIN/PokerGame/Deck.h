#ifndef DECK_H
#define DECK_H

#include "Card.h"

class Deck {
private:
    Card cards[52]; //fixed array here

public:
    Deck();

    void printDeck() const;
    void shuffle();
    //Card deal();
    void reset();
};

#endif
