#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include "Button.h"

#include <iostream>

enum Mode {MENU, BASIC};

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

    
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;

    SDL_Event event;

    bool isRunning;
    Mode mode;

    Button* basicButton;

    void renderMenu();
    void handleMenuInput(SDL_Event& event);


};
