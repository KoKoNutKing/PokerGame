#include "Core/LeaderBoard.h"

void LeaderBoard::getData(const std::string& filename) {
    data = readFromCSV(filename);
}

void LeaderBoard::mySort() {
    for (size_t i = 0; i < data.size(); ++i) {
        for (size_t j = 0; j < data.size() - i - 1; ++j) {
            int total1 = data[j].totalBasic + data[j].totalFive;
            int win1 = data[j].totalBasicWins + data[j].totalFiveWins;
            int total2 = data[j + 1].totalBasic + data[j + 1].totalFive;
            int win2 = data[j + 1].totalBasicWins + data[j + 1].totalFiveWins;
            float score1 = (total1 != 0) ? (float)win1 / total1 : 0.0f;
            float score2 = (total2 != 0) ? (float)win2 / total2 : 0.0f;

            if (score1 < score2) {
                // Swap the elements if the first element's score is less than the second element's score
                std::swap(data[j], data[j + 1]);
            }
        }
    }
}

void LeaderBoard::display(int n) {
    mySort();
    std::cout << "Leaderboard:\n";
    std::cout << std::setw(15) << " Name" 
              << std::setw(15) << " BasicPlayed" 
              << std::setw(15) << " BasicWon" 
              << std::setw(15) << " Five-StudPlayed" 
              << std::setw(15) << " Five-StudWon " 
              << std::setw(10) << " WinRate\n";
    for (int i = 0; i < n && i < (int)data.size(); ++i) {
        if ((data[i].totalBasic + data[i].totalFive) >= 10) { // Only show players with enough games
            float basicWinRate = (data[i].totalBasic != 0) 
                ? (float)data[i].totalBasicWins / data[i].totalBasic 
                : 0.0f;

            float fiveStudWinRate = (data[i].totalFive != 0) 
                ? (float)data[i].totalFiveWins / data[i].totalFive 
                : 0.0f;

            std::cout << std::setw(15) << data[i].name
                      << std::setw(15) << data[i].totalBasic
                      << std::setw(15) << data[i].totalBasicWins
                      << std::setw(15) << data[i].totalFive
                      << std::setw(15) << data[i].totalFiveWins
                      << std::setw(10) << std::fixed << std::setprecision(2) 
                      << ((basicWinRate + fiveStudWinRate) / 2) << "\n";
        }          
    }
}