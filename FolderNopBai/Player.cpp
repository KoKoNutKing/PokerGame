#include "Player.h"

//Support function
bool compareCards(const Card &card1, const Card &card2);
bool isFlush(const std::vector<Card>& hand);
bool isStraight(const std::vector<Card>& hand);


//Card related
void Player::sortHand() {
    std::sort(hand.begin(), hand.end(), compareCards);
}

void Player::displayHand() {
    sortHand();
    for (int i = 0; i < 5; ++i) {
        hand[i].displayCard();
        std::cout << "| ";
    }
    std::cout << std::endl;
}

std::pair<int, int> Player::evaluateHand() const {
    if (isFlush(hand) && isStraight(hand)) {
        return {9, hand[-1].rank}; // Straight Flush
    }
    if (isStraight(hand)) {
        return {5, hand[-1].rank}; // Straight
    }
    if (isFlush(hand)) {
        return {6, hand[-1].rank}; // Flush
    }
    std::map<int, int> rankCounts;
    for (const Card &card : hand) {
        ++rankCounts[card.rank];
    }
    std::vector<std::pair<int, int>> vec(rankCounts.begin(), rankCounts.end());
    //sort by count in descending order
    std::sort(vec.begin(), vec.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return a.second > b.second; 
    });
    
    //vec[i] will be something like this: {rank, count} or {9, 4}
    if (vec[0].second == 4) {
        return {8, vec[0].first}; // Four of a Kind
    }
    if (vec[0].second == 3 && vec[1].second == 2) {
        return {7, vec[0].first}; // Full House
    }
    if (vec[0].second == 3 && vec[1].second == 1) {
        return {4, vec[0].first}; // Three of a Kind
    }
    if (vec[0].second == 2 && vec[1].second == 2) {
        return {3, vec[0].first}; // Two Pair
    }
    if (vec[0].second == 2 && vec[1].second == 1 && vec[2].second == 1) {
        return {2, vec[0].first}; // One Pair
    }

    return {1, vec[-1].first}; // High Card
}


//
void Player::updateWinrate() {
    int totalGames = wins + losses + draws;
    winrate = totalGames > 0 ? (static_cast<double>(wins) / totalGames * 100) : 0.0;
}
void Player::updateFavoriteHand() {
    std::string handStr;
    for (const auto& card : hand) {
        handStr += std::to_string(card.rank) + "_";
    }
    handHistory[handStr]++;
}

std::string Player::getFavoriteHand() const {
    std::string favoriteHand;
    int maxCount = 0;
    for (const auto& entry : handHistory) {
        if (entry.second > maxCount) {
            maxCount = entry.second;
            favoriteHand = entry.first;
        }
    }
    return favoriteHand;
}

//Support func
bool compareCards(const Card &card1, const Card &card2) {
    // Compare by value first
    int value1 = card1.rank;
    int value2 = card2.rank;
    if (value1 != value2) {
        return value1 < value2;
    }
    // If values are the same, compare by suit
    return card1.suit < card2.suit;
}

bool isFlush(const std::vector<Card>& hand) {
    char suit = hand[0].suit;
    for (const auto& card : hand) {
        if (card.suit != suit) return false;
    }
    return true;
}

bool isStraight(const std::vector<Card>& hand) {
    for (int i = 1; i < hand.size(); ++i) {
        if (hand[i].rank != hand[i-1].rank + 1) return false;
    }
    return true;
}