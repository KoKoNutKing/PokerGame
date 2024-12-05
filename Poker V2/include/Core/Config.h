#pragma once

#include <string>

#include "SDL2/SDL.h"



struct Config {

    // Screen configuration
    static inline int ScreenWidth = 1280;
    static inline int ScreenHeight = 720;
    static inline int FPS = 60; 
    static inline const char* WindowTitle = "KoKoNut's Poker";


    // Card configuration
    static inline int CardWidth = 225;  
    static inline int CardHeight = 315; 

    static inline const char* FaceUpCard = "resrc\\CardsSprite.png";
    static inline const char* FaceDownCard = "resrc\\CardsSprite.png"; // not in use
    
    //Player
    static inline const char* DefaultAva = "resrc\\avatar.png";
    //Data File
    static inline const char* DataPath = "resrc\\PlayerData.csv";

    // BackGround 
    static inline SDL_Rect BgSrcRect = { 0, 0, ScreenWidth, ScreenHeight };
    static inline SDL_Rect BgDestRect = { 0, 0, ScreenWidth, ScreenHeight };

    static inline const char* MenuPath = "resrc\\menu.png";
    static inline const char* InitingPath = "resrc\\BasicInitingBg.png";
    static inline const char* BasicGetNumPath = "resrc\\BasicGetNumPath.png";
    static inline const char* BasicGetPlPath = "resrc\\BasicGetPlPath.png";
    static inline const char* BasicPlayingPath = "resrc\\BasicPlaying.png";
    static inline const char* FiveStudPath = "resrc\\updateSoon.png";


    // TextBox settings
    static inline int playerNumberBoxWidth = 200;
    static inline int playerNumberBoxHeight = 50;
    static inline int playerNumberBoxX = 100;
    static inline int playerNumberBoxY = 100;

    // Menu Button settings
    static inline int midButtonWidth = 200;
    static inline int midButtonHeight = 75;
    static inline int midButtonX = ScreenWidth / 2 - midButtonWidth / 2;
    static inline int midButtonY = ScreenHeight * 0.7;

    static inline int backButtonWidth = 200;
    static inline int backButtonHeight = 75;
    static inline int backButtonX = ScreenWidth * 0.9 - midButtonWidth / 2;
    static inline int backButtonY = ScreenHeight * 0.9- midButtonHeight / 2;


    // Button settings
    static inline int getPlayerNumButtonWidth = 100;
    static inline int getPlayerNumButtonHeight = 50;
    static inline int getPlayerNumButtonX = ScreenWidth / 2 - getPlayerNumButtonWidth;
    static inline int getPlayerNumButtonY = ScreenHeight / 2 - getPlayerNumButtonHeight;

    static inline int addPlayerButtonWidth = 50;
    static inline int addPlayerButtonHeight = 50;
    static inline int addPlayerButtonX = getPlayerNumButtonX + 150;
    static inline int addPlayerButtonY = getPlayerNumButtonY;

    static inline int subPlayerButtonWidth = 50;
    static inline int subPlayerButtonHeight = 50;
    static inline int subPlayerButtonX = getPlayerNumButtonX - 100;
    static inline int subPlayerButtonY = getPlayerNumButtonY;

    static inline int getPlayerNameButtonWidth = 100;
    static inline int getPlayerNameButtonHeight = 50;
    static inline int getPlayerNameButtonX = 200;
    static inline int getPlayerNameButtonY = 300;

    static inline int startButtonWidth = 200;
    static inline int startButtonHeight = 75;
    static inline int startButtonX = ScreenWidth * 0.9 - startButtonWidth / 2;
    static inline int startButtonY = ScreenHeight * 0.8 - startButtonHeight / 2;




    // Other configurations
};
struct PlayerData {
    std::string name;
    int totalBasic;
    int totalBasicWins;

    int totalFive;
    int totalFiveWins;
};
