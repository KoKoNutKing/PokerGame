#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <map>

#include "Card.h"


struct Player {
    std::string name;
    Card hand[5];
    int wins = 0;
    int losses = 0;
    int draws = 0;
    double winrate = 0.0;
    std::map<std::string, int> handHistory;
    
    
    void displayHand();
    void updateWinrate();
    void updateFavoriteHand() ;
    std::string getFavoriteHand() const;
};

#endif