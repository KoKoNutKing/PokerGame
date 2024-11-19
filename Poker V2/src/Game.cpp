#include "Game.h"
#include "TextureManager.h"
#include "Card.h"

Card* card;   
Card* card2;   
Button* basicButton;

Game::Game() : window(nullptr), renderer(nullptr), font(nullptr), isRunning(false), mode(MENU) {
    basicButton = nullptr;
}

Game::~Game() {

}    
    
void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "SDL Init Success" << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window) {
            std::cout << "window created" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "renderer created" << std::endl;
        }

        // Initialize SDL_ttf
        if (TTF_Init() == -1) {
            SDL_Log("Failed to initialize SDL_ttf: %s", TTF_GetError());
            isRunning = false;
            return;
        }

        // Load font
        font = TTF_OpenFont("resrc/arial.ttf", 24);
        if (!font) {
            SDL_Log("Failed to load font: %s", TTF_GetError());
            isRunning = false;
            return;
        }

        isRunning = true;
    } else {
        isRunning = false;
    }

   card = new Card(renderer, 0, 0, DIAMONDS, TWO); //
   card2 = new Card(renderer, 300, 300, CLUBS, ACE); //
   basicButton = new Button(renderer, 200, 150, 200, 50, "Basic", font);


}

void Game::handleEvents() {
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            if (mode == MENU) {
                handleMenuInput(event);
            }
        default:
            break;
    }
}
void Game::update() {
    card->update();
    card2->update();

}
void Game::render() {
    SDL_RenderClear(renderer);
    //start rendering part
    if (mode == MENU) {
        //render menu
        basicButton->render(renderer);

    } else {
        card->render();
        card2->render();
    }
    //
    SDL_RenderPresent(renderer);
}
void Game::clean() {
    if (font) {
        TTF_CloseFont(font);
    }
    TTF_Quit(); // Quit SDL_ttf
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::renderMenu() { //Something wrong

}

void Game::handleMenuInput(SDL_Event& event) {
    switch (event.key.keysym.sym) {
        case SDLK_RETURN: // Start the game
            mode = BASIC;
            break;
        case SDLK_ESCAPE: // Quit the game
            isRunning = false;
            break;
    }
}

