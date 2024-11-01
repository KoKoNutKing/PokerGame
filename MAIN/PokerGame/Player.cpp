#include "Player.h"
#include <iostream>

// Constructor
Player::Player(const std::string& name) : name(name), shape(50.f) {
    shape.setFillColor(sf::Color::White);
}

// Destructor
Player::~Player() {}

// Get the player's name
std::string Player::getName() const {
    return name;
}

// Add a card to the player's hand
void Player::addCard(const Card& card) {
    hand.push_back(card);
}

// Remove a card from the player's hand
//Card Player::removeCard() {
//    if (!hand.empty()) {
//        Card card = hand.back();
//        hand.pop_back();
//        return card;
//    }
//    else {
//        throw std::out_of_range("No cards left to remove");
//    }
//}

// Display the player's hand
void Player::showHand() const {
    for (const auto& card : hand) {
        std::cout << card.toString() << std::endl;
    }
}

sf::CircleShape& Player::getShape() {
    return shape;
}