#include "Core/LeaderBoard.h"

void LeaderBoard::getData(const std::string& filename) {
    data = readFromCSV(filename);
}

void LeaderBoard::display(int n) {
    // Sort players by their score (totalBasicWins / totalBasic)
    // std::sort(data.begin(), data.end(), scoreComparator());
    mySort();
    // Display the leaderboard
    std::cout << "Leaderboard:\n";
    for (int i = 0; i < n && i < (int)data.size(); ++i) {
        // Avoid division by zero, display 0 if totalBasic is 0
        float score = (data[i].totalBasic != 0) ? (float)data[i].totalBasicWins / data[i].totalBasic : 0.0f;
        std::cout << data[i].name << ": " << score << std::endl;
    }
}

bool LeaderBoard::scoreComparator() {
    // Calculate the score for each player (totalBasicWins / totalBasic)
    return 1;
}

void LeaderBoard::mySort() {
        for (size_t i = 0; i < data.size(); ++i) {
        for (size_t j = 0; j < data.size() - i - 1; ++j) {
            float score1 = (data[j].totalBasic != 0) ? (float)data[j].totalBasicWins / data[j].totalBasic : 0.0f;
            float score2 = (data[j + 1].totalBasic != 0) ? (float)data[j + 1].totalBasicWins / data[j + 1].totalBasic : 0.0f;

            if (score1 < score2) {
                // Swap the elements if the first element's score is less than the second element's score
                std::swap(data[j], data[j + 1]);
            }
        }
    }
}