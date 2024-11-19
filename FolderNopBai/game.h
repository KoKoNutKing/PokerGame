#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <map>
#include <random>
#include <iomanip>

#include "Player.h"
#include "Deck.h"

struct Game {
    std::vector<Player> players; // nguoi choi
    Deck deck; //ban choi

    void initGame(); //khoi tao game
    void dealHand(Deck deck, Player& player, int& deckIndex); //chia bai
    void displayGameBoard(); //bang

    int compareHands(const Player& p1, const Player& p2); //so sanh
    void determineAndDisplayWinner();// chi ra nguoi thang

    void displayPlayerStats(const Player& player); //thong ke
    void displayLeaderboard();//bang thong ke

    void startGame(); //bat dau choi
};



#endif
