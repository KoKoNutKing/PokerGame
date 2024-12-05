#pragma once

#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Core/Config.h" 
#include "Core/FileHandler.h"


class LeaderBoard {
public:
    void getData(const std::string& filename);

    void mySort();

    void display(int n);

private:
    // Store player data
    std::vector<PlayerData> data;

    // Comparator to sort players by their score (totalBasicWins / totalBasic)
};

