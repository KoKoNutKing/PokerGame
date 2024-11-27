#pragma once

#include <string>
#include <vector>

class CSVHandler {
public:
    CSVHandler(const std::string& filePath);

    // Read all rows from the CSV
    std::vector<std::vector<std::string>> readAll();

    // Write a row to the CSV (appends)
    void writeRow(const std::vector<std::string>& row);

    // Update a specific player's score or add new
    void updateRow(const std::string& key, const std::string& newValue);

    

private:
    std::string filePath;

    // Helper: split a line into tokens
    std::vector<std::string> splitLine(const std::string& line, char delimiter);
};

/*
ten, so tran basic, so tran win basic, tuong tu che do khac,   
.csv
"HOc", 12, 3
"linh", 10, 3


*/