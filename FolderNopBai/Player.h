#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>

#include "Card.h"


struct Player {
    std::string name;
    std::vector<Card> hand;
    int wins = 0;
    int losses = 0;
    int draws = 0;
    double winrate = 0.0;
    std::map<std::string, int> handHistory;
    
    //Cards related
    void sortHand();
    void displayHand();
    std::pair<int, int> evaluateHand() const;


    void updateWinrate();
    void updateFavoriteHand() ;
    std::string getFavoriteHand() const;
};

#endif