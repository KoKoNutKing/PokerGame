#include <iostream>
#include "Card.h"
    
void Card::displayCard() const {
    std::cout << RANKS[rank - 2] << " of " << SUITS[suit] << std::endl;
}