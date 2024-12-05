#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <map>

using namespace std;

enum suit_t { CLUBS, DIAMONDS, HEARTS, SPADES };
enum rank_t { TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };

struct card_t {
    rank_t rank;
    suit_t suit;
};

struct player_t {
    string username;
    vector<card_t> faceup_cards;  // Bài ngửa (2 lá duy nhất)
    int wins = 0;
    int draws = 0;
    int losses = 0;
    double win_rate = 0.0;
};

// Function to create a full deck of cards
vector<card_t> create_deck() {
    vector<card_t> deck;
    for (int s = CLUBS; s <= SPADES; ++s) {
        for (int r = TWO; r <= ACE; ++r) {
            deck.push_back({static_cast<rank_t>(r), static_cast<suit_t>(s)});
        }
    }
    return deck;
}

// Shuffle the deck
void shuffle_deck(vector<card_t>& deck) {
    mt19937 g(random_device{}());
    shuffle(deck.begin(), deck.end(), g);
}

// Shuffle players order
void shuffle_players(vector<player_t>& players) { // co se xoa
    mt19937 g(random_device{}());
    shuffle(players.begin(), players.end(), g);
}

// Deal cards for Five-Card Stud
void deal_cards(vector<card_t>& deck, vector<player_t>& players, vector<card_t>& shared_cards) {
    int deck_index = 0;

    // Clear previous cards
    shared_cards.clear();
    for (auto& player : players) {
        player.faceup_cards.clear();
    }

    // Deal 3 shared facedown cards
    for (int i = 0; i < 3; ++i) {
        shared_cards.push_back(deck[deck_index++]);
    }

    // Deal 2 faceup cards to each player
    for (auto& player : players) {
        for (int i = 0; i < 2; ++i) {
            player.faceup_cards.push_back(deck[deck_index++]);
        }
    }
}

// Display the shared facedown cards
void display_shared_cards(const vector<card_t>& shared_cards) {
    const string ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    const string suits[] = {"Clubs", "Diamonds", "Hearts", "Spades"};

    for (const auto& card : shared_cards) {
        cout << ranks[card.rank - 2] << " of " << suits[card.suit] << "\n";
    }
    cout << "----------------------------\n";
}

// Display a player's hand
void display_hand(const player_t& player) {
    const string ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    const string suits[] = {"Clubs", "Diamonds", "Hearts", "Spades"};

    for (const auto& card : player.faceup_cards) {
        cout << ranks[card.rank - 2] << " of " << suits[card.suit] << "\n";
    }
}

// Evaluate a player's best hand using shared cards
int evaluate_hand(const player_t& player, const vector<card_t>& shared_cards) {
    vector<card_t> all_cards = player.faceup_cards;
    all_cards.insert(all_cards.end(), shared_cards.begin(), shared_cards.end());

    // Count ranks and suits
    map<int, int> rank_count;
    map<int, int> suit_count;
    vector<int> ranks;

    for (const auto& card : all_cards) {
        rank_count[card.rank]++;
        suit_count[card.suit]++;
        ranks.push_back(card.rank);
    }

    sort(ranks.begin(), ranks.end());

    // Check hand rankings
    bool is_flush = any_of(suit_count.begin(), suit_count.end(), [](const auto& p) { return p.second >= 5; });
    bool is_straight = adjacent_find(ranks.begin(), ranks.end(), [](int a, int b) { return b != a + 1; }) == ranks.end();

    if (is_flush && is_straight) return 9; // Straight Flush
    if (any_of(rank_count.begin(), rank_count.end(), [](const auto& p) { return p.second == 4; })) return 8; // Four of a Kind
    if (rank_count.size() == 2) return 7; // Full House
    if (is_flush) return 6; // Flush
    if (is_straight) return 5; // Straight
    if (any_of(rank_count.begin(), rank_count.end(), [](const auto& p) { return p.second == 3; })) return 4; // Three of a Kind
    if (rank_count.size() == 3) return 3; // Two Pair
    if (rank_count.size() == 4) return 2; // One Pair
    return 1; // High Card
}

// Determine the winner
player_t* determine_winner(vector<player_t>& players, const vector<card_t>& shared_cards) {
    player_t* best_player = nullptr;
    int highest_rank = 0;

    for (auto& player : players) {
        int rank = evaluate_hand(player, shared_cards);
        if (rank > highest_rank) {
            highest_rank = rank;
            best_player = &player;
        }
    }

    return best_player;
}

void update_win_rate(player_t& player) {
    int total_games = player.wins + player.draws + player.losses;
    player.win_rate = total_games > 0 ? (double)player.wins / total_games * 100 : 0.0;
}

void print_player_statistics(const vector<player_t>& players) {
    cout << "\nPlayer Statistics:\n";
    for (const auto& player : players) {
        cout << player.username << ": Wins = " << player.wins
             << ", Draws = " << player.draws
             << ", Win Rate = " << player.win_rate << "%\n";
    }
}
void print_leaderboard(vector<player_t> players) {
    // Sắp xếp người chơi theo số lượng chiến thắng (giảm dần)
    sort(players.begin(), players.end(), [](const player_t& a, const player_t& b) {
        return a.wins > b.wins;
    });

    // Hiển thị bảng xếp hạng
    cout << "\n===== Leaderboard =====\n";
    cout << "Rank\tPlayer\t\tWins\tGames Played\tWin Rate\n";
    cout << "--------------------------------------------------\n";
    for (size_t i = 0; i < players.size(); ++i) {
        int total_games = players[i].wins + players[i].draws + players[i].losses;
        cout << i + 1 << "\t" << players[i].username
             << "\t\t" << players[i].wins
             << "\t" << total_games
             << "\t\t" << players[i].win_rate << "%\n";
    }
    cout << "==================================================\n";
}

int main() {
    vector<player_t> players;
    vector<card_t> shared_cards;
    int num_players;
    char play_again;

    cout << "Enter the number of players: ";
    cin >> num_players;

    for (int i = 0; i < num_players; ++i) {
        player_t player;
        cout << "Enter username for player " << i + 1 << ": ";
        cin >> player.username;
        players.push_back(player);
    }

    do {
        auto deck = create_deck();
        shuffle_deck(deck);
        //shuffle_players(players);
        deal_cards(deck, players, shared_cards);

        cout << "\nShared Facedown Cards:\n";
        display_shared_cards(shared_cards);

        cout << "\nHands dealt:\n";
        for (const auto& player : players) {
            cout << player.username << "'s hand:\n";
            display_hand(player);
            cout << "----------------------------\n";
        }

        auto winner = determine_winner(players, shared_cards);
        if (winner) {
            cout << winner->username << " wins!\n";
            winner->wins++;
        } else {
            cout << "It's a draw!\n";
        }

        for (auto& player : players) {
            update_win_rate(player);
        }
        print_player_statistics(players);
        print_leaderboard(players);
        cout << "Do you want to play again? (y/n): ";
        cin >> play_again;

    } while (tolower(play_again) == 'y');

    cout << "Thank you for playing!\n";
    return 0;
}