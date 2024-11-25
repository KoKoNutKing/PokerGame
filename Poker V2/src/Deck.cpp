#include "Core/Deck.h"
#include <random>
#include <iostream>

// Constructor
Deck::Deck(SDL_Renderer* ren) : renderer(ren), currentIndex(0) {
    // Initialize all pointers to null
    for (int i = 0; i < 52; ++i) {
        cards[i] = nullptr;
    }
}

// Destructor
Deck::~Deck() {

}


// Create the deck
void Deck::createDeck() {
    std::cout << "Creating";
    int index = 0;

    for (int s = 0; s < 4; ++s) {
        for (int r = 2; r < 15; ++r) {
            cards[index] = new Card(renderer, 0, 0, static_cast<Suit>(s), static_cast<Rank>(r));
            if (!cards[index]) {
                std::cerr << "Error: Failed to create card at index " << index << std::endl;
            }

            ++index;
        }
    }
}

// Shuffle the deck
void Deck::shuffleDeck() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards, cards + 52, g);  // Shuffle the deck of 52 cards
}

// Draw a card from the deck
Card* Deck::drawCard(int index) {
    if (index >= 0 && index < 52) {
        return cards[index];
    }
    std::cerr << "Invalid card index!" << std::endl;
    return nullptr;
}

// Check the deck's contents
void Deck::checkDeck() const {
    for (int i = 0; i < 52; ++i) {
        if (cards[i] == nullptr) {
            std::cerr << "Error: Card " << i << " is null!" << std::endl;
        } else {
            std::cout << "Card " << i << ": " << cards[i]->rank << " of " << cards[i]->suit << std::endl;
        }
    }
}
