#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include "Core/Card.h"
#include "Core/Player.h"
#include "Core/TextureManager.h"
#include "Core/Basic.h"

#include "Core/Config.h"

#include "UI/Button.h"
#include "UI/InputBox.h"


enum Mode {MENU, BASIC};

class Basic;

class Game {
public:
    Game();
    ~Game();

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

    void handleEvents();
    void update();
    void render();
    void clean();

    bool running() {return isRunning;}

    void renderLoadingScreen(const std::string& message);
    void renderBackGround(const std::string& link);
    
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;

    SDL_Event event;

    bool isRunning;
    Mode mode;
    Basic* basic;


    Button* basicButton;
    Button* backButton;

    void renderMenu();
    void handleMenuInput(SDL_Event& event);


};
