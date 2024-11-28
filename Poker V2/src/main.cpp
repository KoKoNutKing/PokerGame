#define SDL_MAIN_HANDLED

#include "Core/Game.h"
#include "Core/Config.h"

Game *game = nullptr;

int main(int argc, const char * argv[]) {
    const int FPS = Config::FPS;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    game = new Game();

    game->init(Config::WindowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Config::ScreenWidth, Config::ScreenHeight, false);

    while (game->running()) {
        frameStart = SDL_GetTicks();
        //menu;
        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }

    }

    game->clean();

    return 0;
}
