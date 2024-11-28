#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Core/Config.h" // For PlayerData and file path

// Player data structure

class LeaderBoard {
public:
    // Get player data from the CSV file
    void getData(const std::string& filename);

    // Display the top 'n' players
    void display(int n);

    void mySort();

private:
    // Store player data
    std::vector<PlayerData> data;

    // Comparator to sort players by their score (totalBasicWins / totalBasic)
    static bool scoreComparator();
};

#endif // LEADERBOARD_H
