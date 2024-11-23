#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "Core/Player.h"
#include "Core/Table.h"
#include "Core/Deck.h"
#include "UI/InputBox.h"
#include "UI/Button.h"
#include "UI/TextBox.h"

enum Phrase {NUMBER, PLAYER, START};

class Table;
class Player;
struct Slot;
class Deck;

class Basic {
public:
    Basic(SDL_Renderer* renderer, TTF_Font* font, SDL_Event& event);
    ~Basic();

    void initBasic(); // Initializes the game mode

    void update();
    void render(); // Renders the table and its contents

    void handleInput(); // Handle input for the game

    void getPlayer(const std::string& name); // Create a player with a name

    //Game rule
    int compareHands(const Player& p1, const Player& p2);
    void determineAndDisplayWinner();
    void dealHand(Deck& deck, Player* player, int& deckIndex);
    void start(); // Start the game after player names are entered

    //Suportive Function (do sth when button click)
    void addNameBox();
    void createTable();

private:
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Event& event;


    TextBox* playerNumberBox; // Box for number of players
    std::vector<InputBox*> playerNameBoxes; // Boxes for player names
    Button* addPlayerButton;
    Button* subPlayerButton;
    Button* getPlayerNumButton; // Button for next phase
    Button* getPlayerNameButton; // Button to start the game
    Button* startButton; // Button to start the game

    int numberOfPlayers;
    std::vector<Player*> players;
    Table* table; 
    std::vector<Slot> basicSlots;
    Deck* deck;

    Phrase phrase;
};


