#ifndef CONFIG_H
#define CONFIG_H

#include <string>

#include "SDL2/SDL.h"



struct Config {

    // Screen configuration
    static inline int ScreenWidth = 1280;
    static inline int ScreenHeight = 720;
    static inline int FPS = 60; 


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
    static inline const char* BasicGetPlPath = "resrc\\menu.png";
    static inline const char* BasicPlayingPath = "resrc\\menu.png";


    // TextBox settings
    static inline int playerNumberBoxWidth = 200;
    static inline int playerNumberBoxHeight = 50;
    static inline int playerNumberBoxX = 100;
    static inline int playerNumberBoxY = 100;

    // Menu Button settings
    static inline int basicButtonWidth = 200;
    static inline int basicButtonHeight = 75;
    static inline int basicButtonX = ScreenWidth / 2 - basicButtonWidth / 2;
    static inline int basicButtonY = ScreenHeight * 0.7;

    static inline int backButtonWidth = 200;
    static inline int backButtonHeight = 75;
    static inline int backButtonX = ScreenWidth * 0.9 - basicButtonWidth / 2;
    static inline int backButtonY = ScreenHeight * 0.9- basicButtonHeight / 2;


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

    static inline int startButtonWidth = 100;
    static inline int startButtonHeight = 50;
    static inline int startButtonX = ScreenWidth / 2 - startButtonWidth;
    static inline int startButtonY = ScreenHeight / 2 - startButtonHeight;




    // Other configurations
    static inline const char* WindowTitle = "KoKoNut's Poker";
};
struct PlayerData {
    std::string name;
    int totalBasic;
    int totalBasicWins;

    
};

#endif // CONFIG_H
