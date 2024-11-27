#include "Core/FileHandler.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Constructor to initialize file path
CSVHandler::CSVHandler(const std::string& filePath) : filePath(filePath) {}

// Read all rows from the CSV
std::vector<std::vector<std::string>> CSVHandler::readAll() {
    std::vector<std::vector<std::string>> data;
    std::ifstream inFile(filePath);

    if (!inFile.is_open()) {
        std::cerr << "Error: Could not open file " << filePath << std::endl;
        return data;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        data.push_back(splitLine(line, ','));
    }

    inFile.close();
    return data;
}

// Write a row to the CSV (appends)
void CSVHandler::writeRow(const std::vector<std::string>& row) {
    std::ofstream outFile(filePath, std::ios::app);

    if (!outFile.is_open()) {
        std::cerr << "Error: Could not write to file " << filePath << std::endl;
        return;
    }

    for (size_t i = 0; i < row.size(); ++i) {
        outFile << row[i];
        if (i < row.size() - 1) {
            outFile << ",";
        }
    }
    outFile << "\n";
    outFile.close();
}

// Update a specific player's score or add new
void CSVHandler::updateRow(const std::string& key, const std::string& newValue) {
    std::ifstream inFile(filePath);
    std::vector<std::vector<std::string>> data;
    bool updated = false;

    if (!inFile.is_open()) {
        std::cerr << "Error: Could not open file " << filePath << std::endl;
        return;
    }

    // Read and update
    std::string line;
    while (std::getline(inFile, line)) {
        auto row = splitLine(line, ',');
        if (!row.empty() && row[0] == key) {
            row[1] = newValue;
            updated = true;
        }
        data.push_back(row);
    }
    inFile.close();

    // Append new if not updated
    if (!updated) {
        data.push_back({key, newValue});
    }

    // Rewrite the file
    std::ofstream outFile(filePath, std::ios::trunc);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not write to file " << filePath << std::endl;
        return;
    }

    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            outFile << row[i];
            if (i < row.size() - 1) {
                outFile << ",";
            }
        }
        outFile << "\n";
    }
    outFile.close();
}

// Helper: Split a line into tokens
std::vector<std::string> CSVHandler::splitLine(const std::string& line, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream stream(line);
    std::string token;

    while (std::getline(stream, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}
