#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <map>
#include <random>
#include <iomanip>

using namespace std;

// Fixed arrays for suits and ranks
const string SUITS[4] = {"Clubs", "Diamonds", "Hearts", "Spades"};
const string RANKS[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};

// Enum for suit and rank types
enum Suit { CLUBS, DIAMONDS, HEARTS, SPADES };
enum Rank { TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };

// Structure for Card
struct Card {
    Rank rank;
    Suit suit;

    // Display card
    void displayCard() const {
        cout << RANKS[rank - 2] << " of " << SUITS[suit] << endl;
    }
};

// Structure for Player
struct Player {
    string name;
    Card hand[5];
    int wins = 0;
    int losses = 0;
    int draws = 0;
    double winrate = 0.0;
    map<string, int> handHistory;

    void updateWinrate() {
        int totalGames = wins + losses + draws;
        winrate = totalGames > 0 ? (static_cast<double>(wins) / totalGames * 100) : 0.0;
    }

    void updateFavoriteHand() {
        string handStr;
        for (const auto& card : hand) {
            handStr += to_string(card.rank) + "_";
        }
        handHistory[handStr]++;
    }

    string getFavoriteHand() const {
        string favoriteHand;
        int maxCount = 0;
        for (const auto& entry : handHistory) {
            if (entry.second > maxCount) {
                maxCount = entry.second;
                favoriteHand = entry.first;
            }
        }
        return favoriteHand;
    }
};

// Game record structure
struct GameRecord {
    string winner;
    string player1;
    string player2;
    int result;

    void saveToFile(const string& filename, const Player players[], int numPlayers) {
        ofstream outfile(filename, ios::app);
        if (outfile.is_open()) {
            outfile << "Game: " << player1 << " vs " << player2 << "\n";
            outfile << (result == 1 ? "Winner: " + player1 : result == -1 ? "Winner: " + player2 : "It's a tie") << "\n";
            for (int i = 0; i < numPlayers; ++i) {
                const Player& player = players[i];
                outfile << player.name << " | Wins: " << player.wins << ", Losses: " << player.losses
                        << ", Draws: " << player.draws << ", Winrate: " << player.winrate << "%\n";
            }
            outfile << "--------------------------\n";
            outfile.close();
        }
    }
};

void displayPlayerStats(const Player& player) {
    cout << "Player: " << player.name << endl;
    cout << "Wins: " << player.wins << endl;
    cout << "Losses: " << player.losses << endl;
    cout << "Draws: " << player.draws << endl;
    cout << "Winrate: " << player.winrate << "%" << endl;
    cout << "Favorite hand: " << player.getFavoriteHand() << endl;
}

void displayLeaderboard(const Player players[], int numPlayers) {
    cout << "\n--- Leaderboard ---" << endl;
    cout << setw(15) << "Player" << setw(10) << "Wins" << setw(10) << "Losses"
         << setw(10) << "Draws" << setw(15) << "Winrate (%)" << endl;
    cout << "-------------------------------------------------------------" << endl;
    for (int i = 0; i < numPlayers; ++i) {
        cout << setw(15) << players[i].name
             << setw(10) << players[i].wins
             << setw(10) << players[i].losses
             << setw(10) << players[i].draws
             << setw(15) << fixed << setprecision(2) << players[i].winrate << "%" << endl;
    }
}

void createDeck(Card deck[52]) {
    int index = 0;
    for (int s = CLUBS; s <= SPADES; ++s) {
        for (int r = TWO; r <= ACE; ++r) {
            deck[index].rank = static_cast<Rank>(r);
            deck[index].suit = static_cast<Suit>(s);
            index++;
        }
    }
}

void shuffleDeck(Card deck[52]) {
    random_device rd;
    mt19937 g(rd());
    shuffle(deck, deck + 52, g);
}

void dealHand(Card deck[52], Player& player, int& deckIndex) {
    for (int i = 0; i < 5; ++i) {
        player.hand[i] = deck[deckIndex++];
    }
}

void displayHand(const Card hand[5]) {
    for (int i = 0; i < 5; ++i) {
        hand[i].displayCard();
    }
}

int compareHands(const Player& p1, const Player& p2) {
    int max1 = 0, max2 = 0;
    for (int i = 0; i < 5; ++i) {
        if (p1.hand[i].rank > max1) max1 = p1.hand[i].rank;
        if (p2.hand[i].rank > max2) max2 = p2.hand[i].rank;
    }

    if (max1 > max2) return 1;
    if (max2 > max1) return -1;
    return 0;  // Tie
}

void displayGameBoard(const Player players[], int numPlayers) {
    cout << "Game Board:" << endl;
    for (int i = 0; i < numPlayers; ++i) {
        cout << players[i].name << "'s hand:" << endl;
        displayHand(players[i].hand);
        cout << "----------------------------" << endl;
    }
}

void determineAndDisplayWinner(Player players[], int numPlayers) {
    Player* winner = &players[0];
    bool tie = false;

    for (int i = 1; i < numPlayers; ++i) {
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
        for (int i = 0; i < numPlayers; ++i) {
            players[i].draws++;
        }
    } else {
        cout << winner->name << " wins!" << endl;
        winner->wins++;
        winner->updateFavoriteHand();
    }
}

int main() {
    int n;
    cout << "Enter the number of players: ";
    cin >> n;

    Player players[n];
    for (int i = 0; i < n; ++i) {
        cout << "Enter name of player " << i + 1 << ": ";
        cin >> players[i].name;
    }

    char replayChoice;
    do {
        Card deck[52];
        createDeck(deck);
        shuffleDeck(deck);

        int deckIndex = 0;

        for (int i = 0; i < n; ++i) {
            dealHand(deck, players[i], deckIndex);
        }

        displayGameBoard(players, n);

        determineAndDisplayWinner(players, n);

        cout << endl << "Statistics:" << endl;
        for (int i = 0; i < n; ++i) {
            players[i].updateWinrate();
            displayPlayerStats(players[i]);
            cout << endl;
        }

        displayLeaderboard(players, n);

        cout << "Do you want to play again? (y/n): ";
        cin >> replayChoice;

    } while (replayChoice == 'y' || replayChoice == 'Y');

    cout << "Thank you for playing!" << endl;

    return 0;
}
