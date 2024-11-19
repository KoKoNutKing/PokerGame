#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <map>
#include <optional>

using namespace std;

enum suit_t { CLUBS, DIAMONDS, HEARTS, SPADES };
enum rank_t { TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };

struct card_t {
    rank_t rank;
    suit_t suit;
};

struct player_t {
    string username;
    vector<card_t> facedown_card; // Bài úp
    vector<card_t> faceup_cards;  // Bài ngửa
    int wins = 0;
    int draws = 0;
    int losses = 0;
    double win_rate = 0.0;
};

vector<card_t> create_deck() {
    vector<card_t> deck;
    for (int s = CLUBS; s <= SPADES; ++s) {
        for (int r = TWO; r <= ACE; ++r) {
            deck.push_back({static_cast<rank_t>(r), static_cast<suit_t>(s)});
        }
    }
    return deck;
}

void shuffle_deck(vector<card_t>& deck) {
    mt19937 g(random_device{}());
    shuffle(deck.begin(), deck.end(), g);
}

/* Thêm hàm shuffle_players
Hàm này sẽ trộn lại thứ tự người chơi mỗi vòng.*/
void shuffle_players(vector<player_t>& players) {
    mt19937 g(random_device{}());
    shuffle(players.begin(), players.end(), g);
}

void sort_player_hand(player_t& player) {
    // Sắp xếp bài ngửa
    sort(player.faceup_cards.begin(), player.faceup_cards.end(), [](const card_t& a, const card_t& b) {
        if (a.rank == b.rank) {
            return a.suit < b.suit; // Nếu rank giống nhau, sắp xếp theo suit
        }
        return a.rank < b.rank; // Sắp xếp theo rank
    });

    // Bài úp không cần sắp xếp vì chỉ có 1 lá
}

void deal_cards(vector<card_t>& deck, vector<player_t>& players) {
    int deck_index = 0;
    for (auto& player : players) {
        player.facedown_card.clear();
        player.faceup_cards.clear();

        // Chia 1 lá bài úp
        player.facedown_card.push_back(deck[deck_index++]);

        // Nếu người chơi thua liên tiếp 3 lần, họ sẽ nhận một lá bài cao hơn
        if (player.losses >= 3) {
            player.faceup_cards.push_back(deck.back());
            deck.pop_back();
        } else {
            player.faceup_cards.push_back(deck[deck_index++]);
        }

        // Chia 3 lá bài ngửa còn lại
        for (int i = player.faceup_cards.size(); i < 4; ++i) {
            player.faceup_cards.push_back(deck[deck_index++]);
        }

        // Sắp xếp bài của người chơi sau khi chia
        sort_player_hand(player);
    }
}



void display_hand(const player_t& player) {
    cout << "Facedown card: [Hidden]\n";
    const string ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    const string suits[] = {"Clubs", "Diamonds", "Hearts", "Spades"};

    cout << "Faceup cards:\n";
    for (const auto& card : player.faceup_cards) {
        cout << ranks[card.rank - 2] << " of " << suits[card.suit] << endl;
    }
}



bool is_straight(const vector<int>& ranks) {
    return (ranks == vector<int>{2, 3, 4, 5, 14}) || adjacent_find(ranks.begin(), ranks.end(), [](int a, int b) { return b != a + 1; }) == ranks.end();
}

int evaluate_hand(const player_t& player) {
    vector<card_t> all_cards = player.faceup_cards;
    all_cards.push_back(player.facedown_card[0]);

    // Dùng hàm đánh giá tay bài tương tự như phiên bản trước
    map<int, int> rank_count;
    map<int, int> suit_count;
    vector<int> ranks;

    for (const auto& card : all_cards) {
        rank_count[card.rank]++;
        suit_count[card.suit]++;
        ranks.push_back(card.rank);
    }

    sort(ranks.begin(), ranks.end());
    bool is_flush = suit_count.size() == 1;
    bool is_straight_hand = (ranks == vector<int>{2, 3, 4, 5, 14}) ||
                            adjacent_find(ranks.begin(), ranks.end(), [](int a, int b) { return b != a + 1; }) == ranks.end();

    if (is_flush && ranks == vector<int>{10, 11, 12, 13, 14}) return 10; // Royal Flush
    if (is_flush && is_straight_hand) return 9; // Straight Flush
    if (rank_count.size() == 2 && any_of(rank_count.begin(), rank_count.end(), [](const auto& p) { return p.second == 4; })) return 8; // Four of a Kind
    if (rank_count.size() == 2) return 7; // Full House
    if (is_flush) return 6; // Flush
    if (is_straight_hand) return 5; // Straight
    if (any_of(rank_count.begin(), rank_count.end(), [](const auto& p) { return p.second == 3; })) return 4; // Three of a Kind
    if (rank_count.size() == 3) return 3; // Two Pair
    if (rank_count.size() == 4) return 2; // One Pair
    return 1; // High Card
}

optional<player_t*> determine_winner(vector<player_t>& players) {
    player_t* winner = &players[0];
    bool is_tie = false;

    for (auto& player : players) {
        if (&player != winner) {
            int result = evaluate_hand(player) - evaluate_hand(*winner);
            if (result > 0) {
                winner = &player;
                is_tie = false;
            } else if (result == 0) {
                is_tie = true;
            }
        }
    }

    return is_tie ? nullopt : optional<player_t*>{winner};
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
    for (size_t i = 0; i < players.size(); ++i) {
        cout << i + 1 << ". " << players[i].username
             << " - Wins: " << players[i].wins
             << ", Win Rate: " << players[i].win_rate << "%\n";
    }
    cout << "=======================\n";
}


int main() {
    vector<player_t> players;
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
        shuffle_players(players); // Trộn thứ tự người chơi mỗi vòng
        deal_cards(deck, players);

        cout << "\nHands dealt:\n";
        for (auto& player : players) {
            cout << player.username << "'s hand:\n";
            display_hand(player);
            cout << "----------------------------\n";
        }

        auto winner = determine_winner(players);
        if (winner) {
            cout << (*winner)->username << " wins!\n";
            (*winner)->wins++;
            for (auto& player : players) {
                if (&player != *winner) player.losses++;
            }
        } else {
            cout << "It's a tie!\n";
            for (auto& player : players) player.draws++;
        }

        for (auto& player : players) update_win_rate(player);
        print_player_statistics(players);
        print_leaderboard(players);

        cout << "Do you want to play again? (y/n): ";
        cin >> play_again;

    } while (tolower(play_again) == 'y');


    cout << "Thank you for playing!\n";
    return 0;
}
