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
    // Clean up the dynamically allocated cards
    for (int i = 0; i < 52; ++i) {
        delete cards[i];  // Delete each Card object in the array
        cards[i] = nullptr;  // Set pointer to nullptr for safety
    }
}


// Create the deck
void Deck::createDeck() {
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
    unsigned int seed = static_cast<unsigned int>(time(0)); 
    srand(seed); //goi seed

    for (int i = 51; i > 0; --i) {
        int j = rand() % (i + 1);  
        std::swap(cards[i], cards[j]);  
    }
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
