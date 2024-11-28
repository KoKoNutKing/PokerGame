#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include <vector>

#include "Core/Config.h"

// Function to read data from a CSV file and return a vector of Players
std::vector<PlayerData> readFromCSV(const std::string& fileName);

// Function to write data to a CSV file
void writeToCSV(const std::string& fileName, const std::vector<PlayerData>& players);

// Function to update or add a new player in the CSV file
void updatePlayerInCSV(const std::string& fileName, const std::string& playerName, int matches, int wins);

#endif // FILEHANDLER_H
