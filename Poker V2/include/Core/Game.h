#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"

#include "Core/Card.h"
#include "Core/Player.h"
#include "Core/TextureManager.h"
#include "Core/Basic.h"
#include "Core/FiveStud.h"
#include "Core/FileHandler.h"
#include "Core/LeaderBoard.h"

#include "Core/Config.h"

#include "UI/Button.h"
#include "UI/InputBox.h"


enum Mode {MENU, BASIC, FIVESTUD};

class Basic;
class FiveStud;
struct PlayerData;


class Game {
public:
    Game();
    ~Game();

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

    void handleEvents();
    void update();
    void render();
    void WriteData(std::vector<PlayerData>);

    bool running() {return isRunning;}

    void renderLoadingScreen(const std::string& message);
    void renderBackGround(const std::string& link);

    
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;

    SDL_Texture* MenuBg;
    SDL_Texture* FiveStudBg;
    SDL_Texture* InitingBg;

    Mix_Music* bgMusic; 

    SDL_Event event;

    bool isRunning;
    Mode mode;
    Basic* basic;
    FiveStud* fiveStud;
    LeaderBoard* leaderBoard;


    Button* basicButton;
    Button* fiveCardButton;
    Button* LeaderBoardButton;
    Button* backButton;



};
