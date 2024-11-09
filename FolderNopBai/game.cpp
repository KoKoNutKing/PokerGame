#include "game.h"

using namespace std;

void Game::initGame() {
    int n;
    cout << "Enter the number of players: ";
    cin >> n;
    players.resize(n);
    for (int i = 0; i < n; ++i) {
        cout << "Enter name of player " << i + 1 << ": ";
        cin >> players[i].name;
    }
    deck.createDeck();
}

void Game::dealHand(Deck deck, Player& player, int& deckIndex) {
    for (int i = 0; i < 5; ++i) {
        player.hand[i] = deck.cards[deckIndex++];
    }
}

void Game::displayGameBoard() {
    cout << "Game Board:" << endl;
    for (int i = 0; i < players.size(); ++i) {
        cout << players[i].name << "'s hand:" << endl;
        players[i].displayHand();
        cout << "----------------------------" << endl;
    }
}

int Game::compareHands(const Player& p1, const Player& p2) {
    int max1 = 0, max2 = 0;
    for (int i = 0; i < 5; ++i) {
        if (p1.hand[i].rank > max1) max1 = p1.hand[i].rank;
        if (p2.hand[i].rank > max2) max2 = p2.hand[i].rank;
    }

    if (max1 > max2) return 1;
    if (max2 > max1) return -1;
    return 0;  // Tie
}

void Game::determineAndDisplayWinner() {
    Player* winner = &players[0];
    bool tie = false;

    for (int i = 1; i < players.size(); ++i) {
        int result = compareHands(*winner, players[i]);
        if (result == -1) {
            winner = &players[i];
            tie = false;
        } else if (result == 0 && winner != &players[i]) {
            tie = true;
        }
    }

    if (tie) {
        cout << "It's a tie!" << endl;
        for (int i = 0; i < players.size(); ++i) {
            players[i].draws++;
        }
    } else {
        cout << winner->name << " wins!" << endl;
        winner->wins++;
        winner->updateFavoriteHand();
    }
}

void Game::displayLeaderboard() {
    cout << "\n--- Leaderboard ---" << endl;
    cout << setw(15) << "Player" << setw(10) << "Wins" << setw(10) << "Losses"
         << setw(10) << "Draws" << setw(15) << "Winrate (%)" << endl;
    cout << "-------------------------------------------------------------" << endl;
    for (int i = 0; i < players.size(); ++i) {
        cout << setw(15) << players[i].name
             << setw(10) << players[i].wins
             << setw(10) << players[i].losses
             << setw(10) << players[i].draws
             << setw(15) << fixed << setprecision(2) << players[i].winrate << "%" << endl;
    }
}

void Game::displayPlayerStats(const Player& player) {
    cout << "Player: " << player.name << endl;
    cout << "Wins: " << player.wins << endl;
    cout << "Losses: " << player.losses << endl;
    cout << "Draws: " << player.draws << endl;
    cout << "Winrate: " << player.winrate << "%" << endl;
    cout << "Favorite hand: " << player.getFavoriteHand() << endl;
}


void Game::startGame() {
    deck.shuffleDeck();

        int deckIndex = 0;

        for (int i = 0; i < players.size(); ++i) {
            dealHand(deck, players[i], deckIndex);
        }

        displayGameBoard();

        determineAndDisplayWinner();

        cout << endl << "Statistics:" << endl;
        for (int i = 0; i < players.size(); ++i) {
            players[i].updateWinrate();
            displayPlayerStats(players[i]);
            cout << endl;
        }

        displayLeaderboard();
}

// Game record structure
// struct GameRecord {
//     string winner;
//     string player1;
//     string player2;
//     int result;

//     void saveToFile(const string& filename, const Player players[], int numPlayers) {
//         ofstream outfile(filename, ios::app);
//         if (outfile.is_open()) {
//             outfile << "Game: " << player1 << " vs " << player2 << "\n";
//             outfile << (result == 1 ? "Winner: " + player1 : result == -1 ? "Winner: " + player2 : "It's a tie") << "\n";
//             for (int i = 0; i < numPlayers; ++i) {
//                 const Player& player = players[i];
//                 outfile << player.name << " | Wins: " << player.wins << ", Losses: " << player.losses
//                         << ", Draws: " << player.draws << ", Winrate: " << player.winrate << "%\n";
//             }
//             outfile << "--------------------------\n";
//             outfile.close();
//         }
//     }
// };









