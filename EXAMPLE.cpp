#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <string>
#include <cstdlib>
#include <fstream>
#include <map>

using namespace std;

// Fixed arrays for suits and ranks (static content)
const string SUITS[4] = {"Clubs", "Diamonds", "Hearts", "Spades"};
const string RANKS[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};

// Khai báo các chất bài
enum Suit { CLUBS, DIAMONDS, HEARTS, SPADES };

// Khai báo các hạng bài
enum Rank { TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };

// Cấu trúc cho một lá bài
struct Card {
    Rank rank;
    Suit suit;

    // Hiển thị lá bài
    void displayCard() const {
        cout << RANKS[rank - 2] << " of " << SUITS[suit] << endl;
    }
};

// Cấu trúc cho tài khoản người chơi
struct Player {
    string name;
    vector<Card> hand;
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

// Cấu trúc cho bảng điểm
struct GameRecord {
    string winner;
    string player1;
    string player2;
    int result;

    void saveToFile(const string& filename, const vector<Player>& players) {
        ofstream outfile(filename, ios::app);
        if (outfile.is_open()) {
            outfile << "Game: " << player1 << " vs " << player2 << "\n";
            outfile << (result == 1 ? "Winner: " + player1 : result == -1 ? "Winner: " + player2 : "It's a tie") << "\n";
            for (const auto& player : players) {
                outfile << player.name << " | Wins: " << player.wins << ", Losses: " << player.losses
                        << ", Draws: " << player.draws << ", Winrate: " << player.winrate << "%\n";
            }
            outfile << "--------------------------\n";
            outfile.close();
        }
    }
};

// Hàm hiển thị thông tin người chơi
void displayPlayerStats(const Player& player) {
    cout << "Player: " << player.name << endl;
    cout << "Wins: " << player.wins << endl;
    cout << "Losses: " << player.losses << endl;
    cout << "Draws: " << player.draws << endl;
    cout << "Winrate: " << player.winrate << "%" << endl;
    cout << "Favorite hand: " << player.getFavoriteHand() << endl;
}

// Khởi tạo bộ bài gồm 52 lá
vector<Card> createDeck() {
    vector<Card> deck;
    for (int s = CLUBS; s <= SPADES; ++s) {
        for (int r = TWO; r <= ACE; ++r) {
            Card card;
            card.rank = static_cast<Rank>(r);
            card.suit = static_cast<Suit>(s);
            deck.push_back(card);
        }
    }
    return deck;
}

// Xáo bài
void shuffleDeck(vector<Card>& deck) {
    srand(time(0));
    random_shuffle(deck.begin(), deck.end());
}

// Chia 5 lá bài cho mỗi người chơi
void dealHand(vector<Card>& deck, Player& player, int& deckIndex) {
    player.hand.clear();  // Xóa tay bài cũ trước khi chia lại
    for (int i = 0; i < 5; ++i) {
        player.hand.push_back(deck[deckIndex++]);
    }
}

// Hiển thị bài của người chơi
void displayHand(const vector<Card>& hand) {
    for (const auto& card : hand) {
        card.displayCard();
    }
}

// So sánh bộ bài của người chơi (dựa vào lá bài lớn nhất)
int compareHands(const Player& p1, const Player& p2) {
    int max1 = 0, max2 = 0;
    for (const auto& card : p1.hand) {
        if (card.rank > max1) max1 = card.rank;
    }
    for (const auto& card : p2.hand) {
        if (card.rank > max2) max2 = card.rank;
    }

    if (max1 > max2) return 1;
    if (max2 > max1) return -1;
    return 0;  // Hòa
}

// Hiển thị bảng trò chơi
void displayGameBoard(const vector<Player>& players) {
    cout << "Game Board:" << endl;
    for (const auto& player : players) {
        cout << player.name << "'s hand:" << endl;
        displayHand(player.hand);
        cout << "----------------------------" << endl;
    }
}

int main() {
    int n;
    cout << "Enter the number of players: ";
    cin >> n;

    vector<Player> players(n);
    for (int i = 0; i < n; ++i) {
        cout << "Enter name of player " << i + 1 << ": ";
        cin >> players[i].name;
    }

    char replayChoice;
    do {
        // Khởi tạo bộ bài và xáo bài
        vector<Card> deck = createDeck();
        shuffleDeck(deck);

        int deckIndex = 0;

        // Chia bài cho từng người chơi
        for (int i = 0; i < n; ++i) {
            dealHand(deck, players[i], deckIndex);
        }

        // Hiển thị bảng trò chơi
        displayGameBoard(players);

        // Tìm người thắng
        Player* winner = &players[0];
        bool tie = false;

        GameRecord record;

        for (int i = 1; i < n; ++i) {
            int result = compareHands(*winner, players[i]);
            if (result == -1) {
                winner = &players[i];  // Cập nhật người thắng
                tie = false;
                record.winner = players[i].name;
            } else if (result == 0) {
                tie = true;  // Trường hợp hòa
            }
            record.player1 = players[0].name;
            record.player2 = players[i].name;
            record.result = result;
        }

        if (!tie) {
            cout << winner->name << " wins!" << endl;
            winner->wins++;
            winner->updateFavoriteHand();
            record.saveToFile("game_record.txt", players);
        } else {
            cout << "It's a tie!" << endl;
            for (int i = 0; i < n; ++i) {
                players[i].draws++;
            }
        }

        // Cập nhật tỉ lệ thắng cho từng người chơi
        cout << endl << "Statistics:" << endl;
        for (auto& player : players) {
            player.updateWinrate();
            displayPlayerStats(player);
            cout << endl;
        }

        // Hỏi người chơi có muốn chơi lại không
        cout << "Do you want to play again? (y/n): ";
        cin >> replayChoice;

    } while (replayChoice == 'y' || replayChoice == 'Y');

    cout << "Thank you for playing!" << endl;

    return 0;
}
