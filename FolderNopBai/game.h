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
    std::vector<Player> players;
    Deck deck;

    void initGame();
    void dealHand(Deck deck, Player& player, int& deckIndex);
    void displayGameBoard();

    int compareHands(const Player& p1, const Player& p2);
    void determineAndDisplayWinner();

    void displayPlayerStats(const Player& player);
    void displayLeaderboard();

    void startGame();
};



#endif