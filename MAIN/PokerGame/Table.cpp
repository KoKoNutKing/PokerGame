#include "Table.h"
#include <iostream>

// Constructor
Table::Table() {}

// Destructor
Table::~Table() {}

// Add a player to the table
bool Table::addPlayer(const Player& player) {
    if (players.size() < MAX_PLAYERS) {
        players.push_back(std::make_shared<Player>(player));
        return true;
    }
    else {
        std::cout << "Table is full. Cannot add more players." << std::endl;
        return false;
    }
}

//// Remove a player from the table
//void Table::removePlayer(const std::string& name) {
//    auto it = std::remove_if(players.begin(), players.end(),
//        &name{
//            return player->getName() == name;
//        });
//    if (it != players.end()) {
//        players.erase(it, players.end());
//        std::cout << name << " has been removed from the table." << std::endl;
//    }
//    else {
//        std::cout << name << " is not at the table." << std::endl;
//    }
//}

// Start the game
void Table::startGame() {
    std::cout << "Game started with " << players.size() << " players." << std::endl;
    // Additional game logic here
}

// Display the table
void Table::drawTable(sf::RenderWindow& window) {
    float centerX = window.getSize().x / 2.0f;
    float centerY = window.getSize().y / 2.0f;
    float circleRadius = players[0]->getShape().getRadius();
    int numPlayers = players.size();
    std::cout << "ok" << std::endl;
    float angleStep = 360.0f / numPlayers;

    for (int i = 0; i < numPlayers; ++i) {
        std::cout << "ok" << std::endl;
        float angle = i * angleStep * 3.14159f / 180.0f; // Convert to radians
        float x = centerX + circleRadius * cos(angle);
        float y = centerY + circleRadius * sin(angle);
        players[i]->getShape().setPosition(x, y);
        window.draw(players[i]->getShape());
    }
}
