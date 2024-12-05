#include "Core/FileHandler.h"

#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

// Read data from a CSV file
vector<PlayerData> readFromCSV(const string& fileName) {
    vector<PlayerData> players;
    ifstream file(fileName);

    if (!file.is_open()) {
        cerr << "Could not open the file: " << fileName << endl;
        return players;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string name, basic, basicWin, five, fivewin;

        if (getline(iss, name, ',') &&
            getline(iss, basic, ',') &&
            getline(iss, basicWin, ',') &&
            getline(iss, five, ',') &&
            getline(iss, fivewin)) {
            PlayerData player;
            player.name = name;
            player.totalBasic = stoi(basic);
            player.totalBasicWins = stoi(basicWin);
            player.totalFive = stoi(five);
            player.totalFiveWins = stoi(fivewin);
            players.push_back(player);
        }
    }

    file.close();
    return players;
}

// Write data to a CSV file
void writeToCSV(const string& fileName, const vector<PlayerData>& players) {
    ofstream file(fileName, ios::trunc); // Overwrite the file
    if (!file.is_open()) {
        cerr << "Could not open the file: " << fileName << endl;
        return;
    }

    for (const auto& player : players) {
        file << player.name << "," << player.totalBasic << "," << player.totalBasicWins 
                            << "," << player.totalFive << "," << player.totalFiveWins <<"\n";
    }

    file.close();
}

// Update or add a new player in the CSV file
void updatePlayerInCSV(const string& fileName, const string& playerName, int basic, int basicWins, int five, int fiveWins) {
    vector<PlayerData> players = readFromCSV(fileName);

    // Check if the player already exists
    bool found = false;
    for (auto& player : players) {
        if (player.name == playerName) {
            player.totalBasic += basic;
            player.totalBasicWins += basicWins;
            player.totalFive += five;
            player.totalFiveWins += fiveWins;
            found = true;
            break;
        }
    }

    // If not found, add a new player
    if (!found) {
        players.push_back({playerName, basic, basicWins, five, fiveWins});
    }

    // Write updated data back to the file
    writeToCSV(fileName, players);
}
