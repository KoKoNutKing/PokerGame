#include "Deck.h"

void Deck::createDeck() {
int index = 0;
for (int s = CLUBS; s <= SPADES; ++s) {
    for (int r = TWO; r <= ACE; ++r) {
        cards[index].rank = static_cast<Rank>(r);
        cards[index].suit = static_cast<Suit>(s);
        index++;
        }
    }
}

void Deck::shuffleDeck() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards, cards + 52, g);
}