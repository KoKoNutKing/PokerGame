#ifndef TABLE_H
#define TABLE_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include <vector>
//#include <memory>

class Table {
public:
    Table(); // Constructor
    ~Table(); // Destructor

    bool addPlayer(const Player& player); // Add a player to the table
    //void removePlayer(const std::string& name); // Remove a player from the table
    void startGame(); // Start the game
    void drawTable(sf::RenderWindow& window); // Display the table

private:
    static const int MAX_PLAYERS = 8;
    std::vector<std::shared_ptr<Player>> players;
};

#endif // TABLE_H
