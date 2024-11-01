#ifndef CARD_H
#define CARD_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

enum Suit { Hearts, Diamonds, Clubs, Spades };
enum Rank { Two = 2, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace };

class Card {
private:
    Suit suit;
    Rank rank;
    sf::Sprite sprite;
    sf::Texture texture;

public:
    Card(); // Default constructor
    Card(Suit suit, Rank rank);
    ~Card(); // Destructor
    std::string toString() const;
    void loadTexture(const std::string& filePath);
    sf::Sprite getSprite() const;
};

#endif
