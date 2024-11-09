#include "Player.h"


void Player::displayHand() {
    for (int i = 0; i < 5; ++i) {
        hand[i].displayCard();
    }
}

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