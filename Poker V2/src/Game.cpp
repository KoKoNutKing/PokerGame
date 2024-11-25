#include "Core/Game.h"



Game::Game() : window(nullptr), renderer(nullptr), font(nullptr), isRunning(false), mode(MENU) {
    basicButton = nullptr;
    basic = nullptr;
}

Game::~Game() {
    delete basicButton; // Clean up the button
    delete basic;       // Clean up the Basic object

    // Clean up SDL and TTF resources
    clean();
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


    basicButton = new Button(renderer, width / 2 - 100, height / 2 - 25, 200, 50, "Basic", font);
    // test = new InputBox(100, 100, 600, 50, font, renderer);



}

void Game::handleEvents() {
    SDL_PollEvent(&event);

    if (mode == BASIC) {
        basic->handleInput();  // Pass the event to Basic for processing
    }

    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (mode == MENU) {
                handleMenuInput(event);
            }
            break;
        default:
            break;
    }
}
void Game::update() {
    if (mode == MENU) {
        
    } else if (mode == BASIC) {
        basic->update();  // Update Basic
    }
}

void Game::render() {
    SDL_RenderClear(renderer);
    //start rendering part
    if (mode == MENU) {
        renderMenu();


    } else if (mode == BASIC) {
        //renderBasic();
        basic->render();
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

void Game::renderLoadingScreen(const std::string& message) {
    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer);

    // Render the loading text
    SDL_Color textColor = { 255, 255, 255, 255 }; // White color
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, message.c_str(), textColor);
    if (textSurface) {
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_FreeSurface(textSurface);

        if (textTexture) {
            int textWidth, textHeight;
            SDL_QueryTexture(textTexture, nullptr, nullptr, &textWidth, &textHeight);
            SDL_Rect textRect = { 200, 200, textWidth, textHeight }; // Centered on screen
            SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
            SDL_DestroyTexture(textTexture);
        } else {
            std::cerr << "Failed to create loading text texture: " << SDL_GetError() << std::endl;
        }
    } else {
        std::cerr << "Failed to create loading text surface: " << TTF_GetError() << std::endl;
    }
}

void Game::renderMenu() { 
    basicButton->render();

}

void Game::handleMenuInput(SDL_Event& event) {
    switch (event.type) {
        case SDL_QUIT: // Quit the game
            isRunning = false;
            break;

        case SDL_MOUSEBUTTONDOWN: { // Handle mouse button clicks
            if (basicButton->isClicked(event.button.x, event.button.y)) {
                renderLoadingScreen("Initializing Basic Mode...");
                SDL_RenderPresent(renderer);
                basic = new Basic(renderer, font, event);
                basic->initBasic();

                mode = BASIC;
            }
        }
    }
}

