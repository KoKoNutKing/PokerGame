#ifndef CARD_H
#define CARD_H

#include <string>

const std::string SUITS[4] = {"Clubs", "Diamonds", "Hearts", "Spades"};
const std::string RANKS[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};

// Enum for suit and rank types
enum Suit { CLUBS, DIAMONDS, HEARTS, SPADES };
enum Rank { TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };

// Structure for Card
struct Card {
    Rank rank;
    Suit suit;

    // Display card
    void displayCard() const;
};


#endif