#include "Core/Deck.h"
#include <random>

Deck::Deck(SDL_Renderer* ren) : renderer(ren), currentIndex(0) {
    createDeck();  // Create deck as soon as the object is instantiated
}

void Deck::createDeck() {
    int index = 0;
    for (int s = CLUBS; s <= SPADES; ++s) {
        for (int r = TWO; r <= ACE; ++r) {
            *cards[index] = Card(renderer, 0, 0, static_cast<Suit>(s), static_cast<Rank>(r));
            index++;
        }
    }
}

void Deck::shuffleDeck() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards, cards + 52, g);  // Shuffle the deck of 52 cards
}
