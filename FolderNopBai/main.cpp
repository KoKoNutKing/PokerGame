#include <iostream>

#include "game.h"

using namespace std;

//to run use this "g++ main.cpp game.cpp Card.cpp Deck.cpp Player.cpp -o game"

int main() {
    Game game;
    game.initGame();
    char replayChoice;

    do {
        game.startGame();

        cout << "Do you want to play again? (y/n): ";
        cin >> replayChoice;

    } while (replayChoice == 'y' || replayChoice == 'Y');

    cout << "Thank you for playing!" << endl;

    return 0;
}