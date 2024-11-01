#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
#include <SFML/Graphics.hpp> //test
#include <vector>
#include <string>

class Player {
public:
    Player(const std::string& name); // Constructor
    ~Player(); // Destructor


    std::string getName() const; // Get the player's name
    void addCard(const Card& card); // Add a card to the player's hand
    //Card removeCard(); // Remove a card from the player's hand
    void showHand() const; // Display the player's hand

    sf::CircleShape& getShape(); //test

private:
    std::string name;
    std::vector<Card> hand;
    sf::CircleShape shape; //test

};

#endif // PLAYER_H
