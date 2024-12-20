#include "Core/Game.h"



Game::Game() : window(nullptr), renderer(nullptr), font(nullptr), isRunning(false), mode(MENU) {
    basicButton = nullptr;
    backButton = nullptr;
    basic = nullptr;
    leaderBoard = nullptr;
}

Game::~Game() {
    if (font) {
        TTF_CloseFont(font);
    }
    TTF_Quit(); 
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    delete basicButton;
    delete backButton;   
    delete basic;
    delete leaderBoard;

    if (bgMusic) {
        Mix_FreeMusic(bgMusic);
    }
    Mix_CloseAudio();

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
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
            SDL_Log("Failed to initialize SDL_mixer: %s", Mix_GetError());
            isRunning = false;
            return;
        }

        // Load audio files
        bgMusic = Mix_LoadMUS("resrc/backgroundMusic.mp3");
        if (!bgMusic) {
            SDL_Log("Failed to load background music: %s", Mix_GetError());
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
    //Backgorund
    if (bgMusic) {
        Mix_PlayMusic(bgMusic, -1); // Play in a loop
    }

    MenuBg = TextureManager::LoadTexture(Config::MenuPath, renderer);
    FiveStudBg = TextureManager::LoadTexture(Config::FiveStudPath, renderer);
    InitingBg = TextureManager::LoadTexture(Config::InitingPath, renderer);

    basicButton = new Button(renderer, 
                            Config::midButtonX - 250, 
                            Config::midButtonY, 
                            Config::midButtonWidth, 
                            Config::midButtonHeight, 
                            "Basic", 
                            font);
    fiveCardButton = new Button(renderer, 
                            Config::midButtonX, 
                            Config::midButtonY, 
                            Config::midButtonWidth, 
                            Config::midButtonHeight, 
                            "5-Card Stud", 
                            font);
    LeaderBoardButton = new Button(renderer, 
                            Config::midButtonX + 250, 
                            Config::midButtonY, 
                            Config::midButtonWidth, 
                            Config::midButtonHeight, 
                            "Leader Board", 
                            font);
    backButton = new Button(renderer,
                             Config::backButtonX, 
                             Config::backButtonY, 
                             Config::backButtonWidth, 
                             Config::backButtonHeight, 
                             "Back", 
                             font);



}

void Game::handleEvents() {
    SDL_PollEvent(&event);

    if (mode == BASIC) {
        basic->handleInput();  // Pass the event to Basic for processing
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (backButton->isClicked(event.button.x, event.button.y)) {
                WriteData(basic->dataSaver); // Save data before switching
                mode = MENU;
            }
        } 
    } else if (mode == FIVESTUD) {
        fiveStud->handleInput();
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (backButton->isClicked(event.button.x, event.button.y)) {
                WriteData(fiveStud->dataSaver); // Save data before switching
                mode = MENU;
            }
        }
    } else if (mode == MENU) {
        if (event.type == SDL_MOUSEBUTTONDOWN) {
             if (basicButton->isClicked(event.button.x, event.button.y)) {
                TextureManager::DrawTexture(InitingBg, renderer, Config::BgSrcRect, Config::BgDestRect);
                SDL_RenderPresent(renderer);
                if (basic) {
                    delete basic;
                    basic = nullptr;
                }
                basic = new Basic(renderer, font, event);
                basic->initBasic();

                mode = BASIC;
            } else if (fiveCardButton->isClicked(event.button.x, event.button.y)) {
                TextureManager::DrawTexture(InitingBg, renderer, Config::BgSrcRect, Config::BgDestRect);
                SDL_RenderPresent(renderer);
                fiveStud = new FiveStud(renderer, font, event);
                fiveStud->initFiveStud();

                mode = FIVESTUD;
            } else if (LeaderBoardButton->isClicked(event.button.x, event.button.y)) {
                leaderBoard = new LeaderBoard;
                leaderBoard->getData(Config::DataPath);
                leaderBoard->display(5); //display 5 top player
            }
        }
    } 

    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
}
void Game::update() { 
    if (mode == MENU) {
        
    } else if (mode == BASIC) {
        basic->update();  // Update Basic

    } else if (mode == FIVESTUD) {
        fiveStud->update();  

    }
}

void Game::render() {
    SDL_RenderClear(renderer);
    //start rendering part
    if (mode == MENU) {
        TextureManager::DrawTexture(MenuBg, renderer, Config::BgSrcRect, Config::BgDestRect);
        basicButton->render();
        fiveCardButton->render();
        LeaderBoardButton->render();

    } else if (mode == BASIC) {
        basic->render();
        backButton->render();
    } else if (mode == FIVESTUD) {
        fiveStud->render();
        backButton->render();
    }
    //
    SDL_RenderPresent(renderer);
}

void Game::WriteData(std::vector<PlayerData> playerData) {
    for (auto & player: playerData) {
        updatePlayerInCSV(Config::DataPath, player.name, player.totalBasic, player.totalBasicWins, player.totalFive, player.totalFiveWins);
    }
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


