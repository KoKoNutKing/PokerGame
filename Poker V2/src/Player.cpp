#include "Core/Player.h"

//Support function
bool compareCards(const Card &card1, const Card &card2);
bool isFlush(const std::vector<Card>& hand);
bool isStraight(const std::vector<Card>& hand);

//Con/Des Player
Player::Player(SDL_Renderer* renderer, const std::string& texturePath, int x, int y)
    : renderer(renderer), playerTexture(nullptr) {
    
    hand = {};

    // Initialize the player's position
    destRect = {x, y, 100, 100};
    srcRect = {0, 0, 1024, 1024};

    playerTexture = TextureManager::LoadTexture(texturePath.c_str(), renderer);

}

Player::~Player() {
    if (playerTexture) {
        SDL_DestroyTexture(playerTexture); // Destroy the texture when the player is destroyed
    }
}

void Player::render(SDL_Renderer* renderer) {
    if (!playerTexture) {
    std::cerr << "Failed to load player texture: " << SDL_GetError() << std::endl;
    }
    SDL_RenderCopy(renderer, playerTexture, &srcRect, &destRect);
}

void Player::setName(const std::string& input) {
    name = input;
}

std::string Player::getName() {
    return name;
}

void Player::setPosition(int x, int y) {
    destRect.x = x;
    destRect.y = y;
}

//Card related
void Player::addCard(const Card &card) {
    hand.push_back(card);
}

void Player::resetHand() {
    hand.clear();
}


void Player::sortHand() {
    std::sort(hand.begin(), hand.end(), compareCards);
}

void Player::renderHand(SDL_Renderer* renderer) {
    sortHand();
    for (int i = 0; i < hand.size(); ++i) {
        hand[i].update(destRect.x + 150 + 150 * i, destRect.y - 25); // may change
        hand[i].render();
    }
}

std::pair<int, int> Player::evaluateHand() const {
    if (isFlush(hand) && isStraight(hand)) {
        return {9, hand.back().rank}; // Straight Flush
    }
    if (isStraight(hand)) {
        return {5, hand.back().rank}; // Straight
    }
    if (isFlush(hand)) {
        return {6, hand.back().rank}; // Flush
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


//Support func (Calcualting Function)
bool compareCards(const Card &card1, const Card &card2) {
    int value1 = card1.rank;
    int value2 = card2.rank;
    if (value1 != value2) {
        return value1 < value2;
    }
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