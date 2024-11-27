#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <map>
#include <sstream>
using namespace std;

// Các enum cho chất và giá trị quân bài
enum suit_t { CLUBS, DIAMONDS, HEARTS, SPADES };
enum rank_t { TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };



struct card_t {
    rank_t rank;
    suit_t suit;
};

struct player_t {
    string username;
    vector<card_t> faceup_cards;  // For Five-Card Stud
    vector<card_t> hand;          // For Draw Poker
    int wins = 0;
    int draws = 0;
    int losses = 0;
    double win_rate = 0.0;
    bool has_replaced = false;    // Thêm cờ để kiểm tra thay bài
};


// Các biến toàn cục
vector<card_t> deck;                // Bộ bài
vector<player_t> players;           // Danh sách người chơi
vector<card_t> shared_cards;        // Lá bài chung (dùng cho Five-Card Stud)
// Function to create a full deck of cards
void create_deck() {
    deck.clear();
    for (int s = CLUBS; s <= SPADES; ++s) {
        for (int r = TWO; r <= ACE; ++r) {
            deck.push_back({static_cast<rank_t>(r), static_cast<suit_t>(s)});
        }
    }
}


// Shuffle the deck
void shuffle_deck() {
    mt19937 g(random_device{}());
    shuffle(deck.begin(), deck.end(), g);
}

// Shuffle players order
void shuffle_players(vector<player_t>& players) {
    mt19937 g(random_device{}());
    shuffle(players.begin(), players.end(), g);
}

// Sắp xếp các lá bài theo thứ tự rank và suit
void sort_cards(vector<card_t>& cards) {
    sort(cards.begin(), cards.end(), [](const card_t& a, const card_t& b) {
        // Prioritize sorting by rank first, then suit
        if (a.rank != b.rank) {
            return a.rank < b.rank;
        }
        return a.suit < b.suit;
    });
}


//draw
void deal_hand(player_t& player, int num_cards) {
    // Clear the old hand
    player.hand.clear();

    // Check if there are enough cards in the deck
    if (deck.size() < num_cards) {
        cout << "Error: Not enough cards in the deck for " << player.username << ".\n";
        return;
    }

    // Deal new cards
    for (int i = 0; i < num_cards; ++i) {
        player.hand.push_back(deck.back());
        deck.pop_back();
    }

    // Sort the hand
    sort_cards(player.hand);
}








// Deal cards for Five-Card Stud
void deal_cards(vector<card_t>& deck, vector<player_t>& players, vector<card_t>& shared_cards) {
    cout << "Deck size at the start of deal_cards: " << deck.size() << endl;

    // Clear previous cards
    shared_cards.clear();
    for (auto& player : players) {
        player.faceup_cards.clear();
    }

    // Deal 3 shared facedown cards
    if (deck.size() < 3) {
        cout << "Error: Not enough cards in the deck for shared cards.\n";
        exit(1);
    }
    for (int i = 0; i < 3; ++i) {
        shared_cards.push_back(deck.back());
        deck.pop_back();
    }

    cout << "Shared cards dealt. Remaining deck size: " << deck.size() << endl;

    // Deal 2 faceup cards to each player
    for (auto& player : players) {
        cout << "Dealing cards to player " << player.username << endl;
        for (int i = 0; i < 2; ++i) {
            if (deck.empty()) {
                cout << "Error: Deck is empty while dealing to " << player.username << ".\n";
                exit(1);
            }
            player.faceup_cards.push_back(deck.back());
            deck.pop_back();
        }
        sort_cards(player.faceup_cards);
    }

    cout << "All cards dealt. Remaining deck size: " << deck.size() << endl;
}



// Display the shared facedown cards
void display_shared_cards(const vector<card_t>& shared_cards) {
    const string ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    const string suits[] = {"Clubs", "Diamonds", "Hearts", "Spades"};

    cout << "Shared Facedown Cards:\n";
    for (const auto& card : shared_cards) {
        cout << ranks[card.rank - 2] << " of " << suits[card.suit] << "\n";
    }
    cout << "----------------------------\n";
}

// Display a player's hand
void display_hand(const player_t& player, bool hidden = true) {
    const string ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    const string suits[] = {"Clubs", "Diamonds", "Hearts", "Spades"};

    if (hidden) {
        cout << "Hand: [Hidden]\n";
    } else {
        cout << "Hand:\n";
        for (const auto& card : player.hand) {  // For Draw Poker
            cout << ranks[card.rank - 2] << " of " << suits[card.suit] << "\n";
        }
    }
}


//draw
void replace_cards(player_t& player) {
    cout << player.username << "'s hand:\n";
    display_hand(player, false);

    vector<int> positions_to_replace;
    cout << "Enter positions (1-5) to replace (0 to keep all): ";
    string input;
    getline(cin >> ws, input);

    if (!input.empty()) {
        istringstream iss(input);
        int pos;
        while (iss >> pos) {
            if (pos >= 1 && pos <= player.hand.size()) {
                positions_to_replace.push_back(pos - 1);
            } else {
                cout << "Invalid position: " << pos << ". Skipping.\n";
            }
        }
    }

    if (positions_to_replace.empty()) {
        cout << player.username << " kept all cards.\n";
    } else {
        for (int pos : positions_to_replace) {
            if (!deck.empty()) {
                player.hand[pos] = deck.back(); // Replace specific card
                deck.pop_back();
            } else {
                cout << "Error: Deck is empty while replacing cards.\n";
                break;
            }
        }
    }

    // Sort the hand after replacements
    sort_cards(player.hand);
}



// Evaluate a player's best hand using shared cards
int evaluate_hand(const player_t& player, const vector<card_t>& shared_cards = {}) {
    vector<card_t> all_cards = player.hand; // Lấy bài trên tay

    // Đảm bảo có ít nhất 5 lá bài
    if (all_cards.size() < 5) {
        cout << "Error: Not enough cards to evaluate hand for " << player.username << ".\n";
        return 0; // Trả về điểm thấp nếu không đủ lá bài
    }

    // Đếm số lượng mỗi rank và suit
    map<int, int> rank_count;
    map<int, int> suit_count;
    for (const auto& card : all_cards) {
        rank_count[card.rank]++;
        suit_count[card.suit]++;
    }

    // Kiểm tra Flush (5 lá cùng chất)
    bool is_flush = any_of(suit_count.begin(), suit_count.end(),
                           [](const auto& p) { return p.second >= 5; });

    // Kiểm tra Straight (liên tiếp 5 lá)
    vector<int> ranks;
    for (const auto& card : all_cards) {
        ranks.push_back(card.rank);
    }
    sort(ranks.begin(), ranks.end(), greater<int>()); // Sắp xếp giảm dần

    bool is_straight = false;
    for (size_t i = 0; i <= ranks.size() - 5; ++i) {
        if (ranks[i] == ranks[i + 1] + 1 &&
            ranks[i + 1] == ranks[i + 2] + 1 &&
            ranks[i + 2] == ranks[i + 3] + 1 &&
            ranks[i + 3] == ranks[i + 4] + 1) {
            is_straight = true;
            break;
        }
    }

    // Kiểm tra các tổ hợp bài
    if (is_flush && is_straight) return 9000 + ranks[0];  // Straight Flush
    if (any_of(rank_count.begin(), rank_count.end(),
               [](const auto& p) { return p.second == 4; })) {
        return 8000 + ranks[0]; // Four of a Kind
    }
    if (rank_count.size() == 2) {
        if (any_of(rank_count.begin(), rank_count.end(),
                   [](const auto& p) { return p.second == 3; })) {
            return 7000 + ranks[0]; // Full House
        }
    }
    if (is_flush) return 6000 + ranks[0];                 // Flush
    if (is_straight) return 5000 + ranks[0];              // Straight
    if (any_of(rank_count.begin(), rank_count.end(),
               [](const auto& p) { return p.second == 3; })) {
        return 4000 + ranks[0]; // Three of a Kind
    }
    if (rank_count.size() == 3) return 3000 + ranks[0];   // Two Pair
    if (rank_count.size() == 4) return 2000 + ranks[0];   // One Pair

    return 1000 + ranks[0]; // High Card
}



// Determine the winners (handles draws)
//Cải thiện hàm determine_winners với tie-breaking:
vector<player_t*> determine_winners(vector<player_t>& players, const vector<card_t>& shared_cards = {}) {
    vector<player_t*> best_players;
    int highest_score = 0;

    // Đánh giá điểm cho từng người chơi
    for (auto& player : players) {
        int score = evaluate_hand(player, shared_cards);
        if (score > highest_score) {
            highest_score = score;
            best_players.clear();
            best_players.push_back(&player);
        } else if (score == highest_score) {
            best_players.push_back(&player);
        }
    }

    // Tie-breaking bằng kicker
    if (best_players.size() > 1) {
        int highest_kicker_score = 0;
        vector<player_t*> kicker_winners;

        for (auto* player : best_players) {
            vector<card_t> all_cards = player->hand; // Lấy bài của người chơi
            sort(all_cards.rbegin(), all_cards.rend(), [](const card_t& a, const card_t& b) {
                return a.rank > b.rank; // Sắp xếp theo giá trị lớn
            });

            int kicker_score = 0;
            for (int i = 0; i < 5; ++i) { // Tính điểm từ 5 lá bài lớn nhất
                if (i < all_cards.size()) {
                    kicker_score = kicker_score * 15 + all_cards[i].rank;
                }
            }

            if (kicker_score > highest_kicker_score) {
                highest_kicker_score = kicker_score;
                kicker_winners.clear();
                kicker_winners.push_back(player);
            } else if (kicker_score == highest_kicker_score) {
                kicker_winners.push_back(player);
            }
        }

        return kicker_winners;
    }

    return best_players;
}






player_t* determine_winner(vector<player_t>& players, const vector<card_t>& shared_cards = {}) {
    vector<player_t*> winners;
    int highest_rank = 0;

    for (auto& player : players) {
        // Truyền thêm shared_cards để tính điểm
        int rank = evaluate_hand(player, shared_cards);
        if (rank > highest_rank) {
            highest_rank = rank;
            winners.clear();
            winners.push_back(&player);
        } else if (rank == highest_rank) {
            winners.push_back(&player);
        }
    }

    // Nếu không hòa, trả về người thắng đầu tiên
    if (winners.size() == 1) {
        return winners[0];
    }

    // Nếu hòa, trả về nullptr để thông báo hòa
    return nullptr;
}




void update_win_rate(player_t& player) {
    int total_games = player.wins + player.draws + player.losses;
    player.win_rate = total_games > 0 ? (double)player.wins / total_games * 100 : 0.0;
}

void print_player_statistics(const vector<player_t>& players) {
    cout << "\nPlayer Statistics:\n";
    for (const auto& player : players) {
        int total_games = player.wins + player.draws + player.losses;
        if (total_games == 0) {
            cout << player.username << ": No games played yet.\n";
        } else {
            cout << player.username << ": Wins = " << player.wins
                 << ", Draws = " << player.draws
                 << ", Losses = " << player.losses
                 << ", Win Rate = " << player.win_rate << "%\n";
        }
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

void display_faceup_cards(const player_t& player) {
    const string ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    const string suits[] = {"Clubs", "Diamonds", "Hearts", "Spades"};

    cout << "Face-Up Cards:\n";
    for (const auto& card : player.faceup_cards) {
        cout << ranks[card.rank - 2] << " of " << suits[card.suit] << "\n";
    }
}

void initialize_players() {
    players.clear();
    int num_players;

    do {
        cout << "Enter the number of players (at least 2): ";
        cin >> num_players;
        if (cin.fail() || num_players < 2) {
            cout << "Invalid input. Please try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            num_players = 0;
        }
    } while (num_players < 2);

    for (int i = 0; i < num_players; ++i) {
        player_t player;
        cout << "Enter username for player " << i + 1 << ": ";
        cin >> player.username;
        players.push_back(player);
    }
}



int select_game_mode() {
    int choice = 0;
    do {
        cout << "Choose a game mode:\n1. Draw Poker\n2. Five-Card Stud\nYour choice: ";
        cin >> choice;
        if (choice != 1 && choice != 2) {
            cout << "Invalid choice. Please select 1 or 2.\n";
        }
    } while (choice != 1 && choice != 2);
    return choice;
}

void play_draw_poker() {
    // Chia bài cho mỗi người chơi
    for (auto& player : players) {
        deal_hand(player, 5);
    }

    // Hiển thị bài ban đầu (ẩn)
    cout << "\nInitial Hands:\n";
    for (const auto& player : players) {
        cout << player.username << "'s hand:\n";
        display_hand(player, true); // Giấu bài ban đầu
        cout << "----------------------------\n";
    }

    cout << "\nFirst betting round...\n";
    cout << "Players place their bets...\n";

    // Thay bài
    for (auto& player : players) {
        replace_cards(player);
    }

    // Hiển thị bài cuối cùng
    cout << "\nFinal Hands:\n";
    for (const auto& player : players) {
        cout << player.username << "'s hand:\n";
        display_hand(player, false); // Hiển thị bài cuối cùng
        cout << "----------------------------\n";
    }

    cout << "\nSecond betting round...\n";
    cout << "Players place their bets...\n";

    // Xác định người thắng
    vector<player_t*> winners;
    int highest_rank = 0;

    for (auto& player : players) {
        int rank = evaluate_hand(player); // Đánh giá bài của người chơi
        if (rank > highest_rank) {
            highest_rank = rank;
            winners.clear();
            winners.push_back(&player);
        } else if (rank == highest_rank) {
            winners.push_back(&player);
        }
    }

    // Hiển thị người thắng hoặc hòa
    if (winners.size() == 1) {
        cout << "\n" << winners[0]->username << " wins with the best hand!\n";
        winners[0]->wins++;
    } else {
        cout << "\nIt's a draw between: ";
        for (auto* winner : winners) {
            cout << winner->username << " ";
            winner->draws++;
        }
        cout << "\n";
    }

    // Cập nhật thống kê cho người thua
    for (auto& player : players) {
        if (std::find(winners.begin(), winners.end(), &player) == winners.end()) {
            player.losses++;
        }
    }
}

void play_five_card_stud() {
    if (deck.size() < players.size() * 2 + 3) {
        cout << "Error: Not enough cards in the deck for Five-Card Stud.\n";
        return;
    }

    // Chia bài chung
    shared_cards.clear();
    for (int i = 0; i < 3; ++i) {
        shared_cards.push_back(deck.back());
        deck.pop_back();
    }

    // Chia bài ngửa
    for (auto& player : players) {
        player.faceup_cards.clear();
        for (int i = 0; i < 2; ++i) {
            player.faceup_cards.push_back(deck.back());
            deck.pop_back();
        }
    }

    // Hiển thị bài chung
    cout << "\nShared Facedown Cards:\n";
    display_shared_cards(shared_cards);

    // Hiển thị bài ngửa của từng người chơi
    cout << "\nPlayers' Face-Up Cards:\n";
    for (const auto& player : players) {
        cout << player.username << "'s cards:\n";
        display_faceup_cards(player);
        cout << "----------------------------\n";
    }

    // Xác định người thắng
    auto winners = determine_winners(players, shared_cards);
    if (winners.empty()) {
        cout << "\nNo valid hands. No winner for this round.\n";
    } else if (winners.size() == 1) {
        cout << "\n" << winners[0]->username << " wins with the best hand!\n";
        winners[0]->wins++;
    } else {
        cout << "\nIt's a draw between: ";
        for (auto* winner : winners) {
            cout << winner->username << " ";
            winner->draws++;
        }
        cout << "\n";
    }

    // Cập nhật thống kê cho những người thua
    for (auto& player : players) {
        if (std::find(winners.begin(), winners.end(), &player) == winners.end()) {
            player.losses++;
        }
    }
}




void update_and_display_leaderboard() {
    for (auto& player : players) {
        update_win_rate(player);
    }

    cout << "\nPlayer Statistics:\n";
    print_player_statistics(players);

    cout << "\nThe leaderboard has been updated! Check your ranking:\n";
    print_leaderboard(players);
}

bool ask_play_again() {
    char play_again;
    do {
        cout << "Do you want to play again? (y/n): ";
        cin >> play_again;
        play_again = tolower(play_again);
        if (play_again != 'y' && play_again != 'n') {
            cout << "Invalid input. Please enter 'y' for yes or 'n' for no.\n";
        }
    } while (play_again != 'y' && play_again != 'n');
    return play_again == 'y';
}


int main() {
    initialize_players();

    int choice;
    do {
        cout << "Choose a game mode:\n1. Draw Poker\n2. Five-Card Stud\nYour choice: ";
        cin >> choice;
        if (choice != 1 && choice != 2) {
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 1 && choice != 2);

    do {
        create_deck();
        shuffle_deck();

        if (deck.size() < players.size() * 2 + 3) {  // Check if deck has enough cards
            cout << "Error: Not enough cards in the deck for this game mode.\n";
            exit(1);
        }

        if (choice == 1) { // Draw Poker
            for (auto& player : players) {
                player.has_replaced = false;
                deal_hand(player, 5);
            }
            play_draw_poker();
        } else if (choice == 2) { // Five-Card Stud
            play_five_card_stud();
        }

        update_and_display_leaderboard();

    } while (ask_play_again());

    cout << "Thank you for playing!\n";
    return 0;
}
