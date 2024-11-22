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

enum Phrase {NUMBER, INIT_PLAYER, PLAYER, START};

class Player;
struct Slot;
class Table;
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
    void start(); // Start the game after player names are entered

private:
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Event& event;

    TextBox* playerNumberBox; // Box for number of players
    std::vector<InputBox*> playerNameBoxes; // Boxes for player names
    Button* addPlayerButton;
    Button* subPlayerButton;
    Button* nextButton; // Button for next phase
    Button* startButton; // Button to start the game

    int numberOfPlayers;
    std::vector<Player> players;
    Table* table; 
    std::vector<Slot> basicSlots;
    Deck* deck;

    Phrase phrase;
};


