#include <iostream>
#include "Card.h"


Card::Card() : suit(Suit::Hearts), rank(Rank::Two) {
    // You can initialize to any default values you prefer
}

// Parameterized constructor
Card::Card(Suit suit, Rank rank) : suit(suit), rank(rank) {
    // Initialization list is used to initialize member variables
}

// Destructor
Card::~Card() {
    // Destructor body, if you need to release resources (not needed in this simple example)
}
std::string Card::toString() const {
    const char* suitNames[] = { "Hearts", "Diamonds", "Clubs", "Spades" };
    const char* rankNames[] = { "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace" };

    return std::string(rankNames[static_cast<int>(rank-2)]) + " of " + suitNames[static_cast<int>(suit)];
}


void Card::loadTexture(const std::string& filePath)
{
}

sf::Sprite Card::getSprite() const
{
	return sf::Sprite();
}
