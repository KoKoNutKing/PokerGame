#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "SDL2/SDL.h"

#include "Core/Player.h"
#include "Core/Table.h"
#include "Core/Deck.h"
#include "Core/TextureManager.h"

#include "Core/Config.h"

#include "UI/InputBox.h"
#include "UI/Button.h"
#include "UI/TextBox.h"

enum Phrase5Stud {NUMBER1, PLAYER1, START1};


class Table;
class Player;
struct PlayerData;
struct Slot;
class Deck;

class FiveStud {
public:
    FiveStud(SDL_Renderer* renderer, TTF_Font* font, SDL_Event& event);
    ~FiveStud();

    void initFiveStud(); 

    void update();
    void render(); 

    void handleInput(); 

    void getPlayer(const std::string& name); 

    //Game rule
    int compareHands(const Player& p1, const Player& p2);

    void renderSharedCard();

    void determineAndDisplayWinner();
    void dealHand(Deck& deck, Player* player, int& deckIndex);
    void start();

    //Suportive Function (do sth when button click)
    void addNameBox();
    void createTable();

    void updateData(std::vector<PlayerData> &data, std::string winnerName);

    std::vector<PlayerData> dataSaver;


private:
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Event& event;

    SDL_Texture* FiveStudGetNumBg;
    SDL_Texture* FiveStudGetPlBg;
    SDL_Texture* FiveStudPlayingBg;

    TextBox* playerNumberBox; // Box for number of players
    std::vector<InputBox*> playerNameBoxes; // Boxes for player names
    std::vector<TextBox*> playerNameDrawer; // Boxes for player names
    Button* addPlayerButton;
    Button* subPlayerButton;
    Button* getPlayerNumButton; // Button for next phase
    Button* getPlayerNameButton; // Button to start the game
    Button* startButton; // Button to start the game
    TextBox* resultBox;


    int numberOfPlayers;
    std::vector<Player*> players;
    Table* table; 
    std::vector<Slot> fiveStudSlots;
    Deck* deck;

    std::vector<Card> sharedCard;

    Phrase5Stud phrase;
};


