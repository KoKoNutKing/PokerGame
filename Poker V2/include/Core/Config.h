// Config.h
#ifndef CONFIG_H
#define CONFIG_H

// Simple structure to hold configuration values
struct Config {
    // Screen configuration
    static inline int ScreenWidth = 1280;   // Default width
    static inline int ScreenHeight = 720; // Default height
    static inline int FPS = 60; 

    // Size configuration
    static inline int CardWidth = 225;  // Default card width
    static inline int CardHeight = 315; // Default card height

    static inline const char* FaceUpCard = "resrc\\CardsSprite.png";
    static inline const char* FaceDownCard = "resrc\\CardsSprite.png";

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
    static inline int addPlayerButtonX = 350;
    static inline int addPlayerButtonY = 100;
    static inline int addPlayerButtonWidth = 50;
    static inline int addPlayerButtonHeight = 50;

    static inline int subPlayerButtonX = 50;
    static inline int subPlayerButtonY = 100;
    static inline int subPlayerButtonWidth = 50;
    static inline int subPlayerButtonHeight = 50;

    static inline int getPlayerNumButtonX = 200;
    static inline int getPlayerNumButtonY = 200;
    static inline int getPlayerNumButtonWidth = 100;
    static inline int getPlayerNumButtonHeight = 50;

    static inline int getPlayerNameButtonX = 200;
    static inline int getPlayerNameButtonY = 300;
    static inline int getPlayerNameButtonWidth = 100;
    static inline int getPlayerNameButtonHeight = 50;

    static inline int startButtonX = 200;
    static inline int startButtonY = 300;
    static inline int startButtonWidth = 100;
    static inline int startButtonHeight = 50;




    // Other configurations
    static inline const char* WindowTitle = "KoKoNut's Poker";
};

#endif // CONFIG_H
