#include "Deck.h"


Deck::Deck() {
    int index = 0;
    for (int suit = 0; suit < 4; ++suit) {
        for (int rank = 2; rank < 15; ++rank) {
            cards[index++] = Card(static_cast<Suit>(suit), static_cast<Rank>(rank));
        }
    }
}

void Deck::printDeck() const {
    for (const auto& card : cards) {
        std::cout << card.toString() << std::endl;
    }
}

void Deck::shuffle()
{
}



void Deck::reset()
{
}
