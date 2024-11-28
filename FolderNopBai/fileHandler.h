#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include <vector>

// Struct for Player
struct Player {
    std::string name;
    int totalMatches;
    int totalWins;
};

// Function to read data from a CSV file and return a vector of Players
std::vector<Player> readFromCSV(const std::string& fileName);

// Function to write data to a CSV file
void writeToCSV(const std::string& fileName, const std::vector<Player>& players);

// Function to update or add a new player in the CSV file
void updatePlayerInCSV(const std::string& fileName, const std::string& playerName, int matches, int wins);

#endif // FILEHANDLER_H
