/*#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

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
        string ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
        string suits[] = {"Clubs", "Diamonds", "Hearts", "Spades"};
        cout << ranks[rank - 2] << " of " << suits[suit] << endl;
    }
};

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
vector<Card> dealHand(vector<Card>& deck, int& deckIndex) {
    vector<Card> hand;
    for (int i = 0; i < 5; ++i) {
        hand.push_back(deck[deckIndex++]);
    }
    return hand;
}

// Hiển thị bài của người chơi
void displayHand(const vector<Card>& hand) {
    for (const auto& card : hand) {
        card.displayCard();
    }
}

// Hàm so sánh hai bộ bài (cơ bản là so sánh lá bài lớn nhất)
int compareHands(const vector<Card>& hand1, const vector<Card>& hand2) {
    int max1 = 0, max2 = 0;
    for (const auto& card : hand1) {
        if (card.rank > max1) max1 = card.rank;
    }
    for (const auto& card : hand2) {
        if (card.rank > max2) max2 = card.rank;
    }

    if (max1 > max2) return 1;  // hand1 thắng
    if (max2 > max1) return -1; // hand2 thắng
    return 0;                   // Hòa
}

int main() {
    // Khởi tạo bộ bài và xáo bài
    vector<Card> deck = createDeck();
    shuffleDeck(deck);

    // Giả sử có 2 người chơi
    int deckIndex = 0;
    vector<Card> player1Hand = dealHand(deck, deckIndex);
    vector<Card> player2Hand = dealHand(deck, deckIndex);

    // Hiển thị bài của 2 người chơi
    cout << "Player 1's hand:" << endl;
    displayHand(player1Hand);
    cout << endl;

    cout << "Player 2's hand:" << endl;
    displayHand(player2Hand);
    cout << endl;

    // So sánh hai bộ bài
    int result = compareHands(player1Hand, player2Hand);
    if (result == 1) {
        cout << "Player 1 wins!" << endl;
    } else if (result == -1) {
        cout << "Player 2 wins!" << endl;
    } else {
        cout << "It's a tie!" << endl;
    }

    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

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
        string ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
        string suits[] = {"Clubs", "Diamonds", "Hearts", "Spades"};
        cout << ranks[rank - 2] << " of " << suits[suit] << endl;
    }
};
struct Player {
    string name;
    int wins;       // Số trận thắng
    int losses;     // Số trận thua
    int draws;      // Số trận hòa
    double winrate; // Tỉ lệ thắng
    vector<string> favoriteStrategies; // Chiến thuật yêu thích (các bộ bài chiến thắng thường xuyên)

    // Khởi tạo
    Player(string playerName) {
        name = playerName;
        wins = 0;
        losses = 0;
        draws = 0;
        winrate = 0.0;
    }

    // Tính toán tỉ lệ thắng
void updateWinrate() {
    int totalGames = wins + losses + draws;
    if (totalGames > 0) {
        winrate = (double)wins / totalGames * 100; // tính % thắng
    } else {
        winrate = 0.0;
    }
}

    // Cập nhật chiến thuật yêu thích
    void addStrategy(string handType) {
        favoriteStrategies.push_back(handType);
        // Có thể thêm logic để xác định chiến thuật nào thường xuyên xuất hiện nhất
    }
};
// Hàm cập nhật kết quả trận đấu
void updatePlayerStats(Player& winner, Player& loser, string winningHand) {
    // Cập nhật số liệu cho người thắng
    winner.wins++;
    winner.addStrategy(winningHand);  // Thêm chiến thuật chiến thắng vào danh sách
    winner.updateWinrate();

    // Cập nhật số liệu cho người thua
    loser.losses++;
    loser.updateWinrate();
}

// Hàm xử lý trường hợp hòa
void updateDrawStats(Player& player1, Player& player2) {
    player1.draws++;
    player1.updateWinrate();

    player2.draws++;
    player2.updateWinrate();
}
// Hàm hiển thị thông tin người chơi
void displayPlayerStats(const Player& player) {
    cout << "Player: " << player.name << endl;
    cout << "Wins: " << player.wins << endl;
    cout << "Losses: " << player.losses << endl;
    cout << "Draws: " << player.draws << endl;
    cout << "Winrate: " << player.winrate << "%" << endl;

    cout << "Favorite Strategies (winning hands): ";
    for (const string& strategy : player.favoriteStrategies) {
        cout << strategy << ", ";
    }
    cout << endl;
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
vector<Card> dealHand(vector<Card>& deck, int& deckIndex) {
    vector<Card> hand;
    for (int i = 0; i < 5; ++i) {
        hand.push_back(deck[deckIndex++]);
    }
    return hand;
}

// Hiển thị bài của người chơi
void displayHand(const vector<Card>& hand) {
    for (const auto& card : hand) {
        card.displayCard();
    }
}

// Hàm so sánh hai bộ bài (cơ bản là so sánh lá bài lớn nhất)
int compareHands(const vector<Card>& hand1, const vector<Card>& hand2) {
    int max1 = 0, max2 = 0;
    for (const auto& card : hand1) {
        if (card.rank > max1) max1 = card.rank;
    }
    for (const auto& card : hand2) {
        if (card.rank > max2) max2 = card.rank;
    }

    if (max1 > max2) return 1;  // hand1 thắng
    if (max2 > max1) return -1; // hand2 thắng
    return 0;                   // Hòa
}

int main() {
    Player player1("Player 1");
    Player player2("Player 2");

    // Khởi tạo bộ bài và chia bài cho hai người chơi
    vector<Card> deck = createDeck();
    shuffleDeck(deck);

    int deckIndex = 0;
    vector<Card> player1Hand = dealHand(deck, deckIndex);
    vector<Card> player2Hand = dealHand(deck, deckIndex);

    cout << "Player 1's hand:" << endl;
    displayHand(player1Hand);
    cout << endl;

    cout << "Player 2's hand:" << endl;
    displayHand(player2Hand);
    cout << endl;

    // So sánh hai bộ bài và cập nhật thông tin
    int result = compareHands(player1Hand, player2Hand);
    if (result == 1) {
        cout << "Player 1 wins!" << endl;
        updatePlayerStats(player1, player2, "Winning Strategy"); // Tùy chỉnh chiến thuật thắng
    } else if (result == -1) {
        cout << "Player 2 wins!" << endl;
        updatePlayerStats(player2, player1, "Winning Strategy");
    } else {
        cout << "It's a tie!" << endl;
        updateDrawStats(player1, player2);
    }

    // Hiển thị thông tin thống kê của hai người chơi
    cout << endl << "Statistics:" << endl;
    displayPlayerStats(player1);
    displayPlayerStats(player2);

    return 0;
}*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

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
        string ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
        string suits[] = {"Clubs", "Diamonds", "Hearts", "Spades"};
        cout << ranks[rank - 2] << " of " << suits[suit] << endl;
    }
};

// Cấu trúc cho người chơi
struct Player {
    string name;
    vector<Card> hand;  // Tay bài của người chơi
    int wins = 0;
    int losses = 0;
    int draws = 0;
    double winrate = 0.0;

    // Cập nhật tỉ lệ thắng
    void updateWinrate() {
        int totalGames = wins + losses + draws;
        if (totalGames > 0) {
            winrate = (double)wins / totalGames * 100;
        } else {
            winrate = 0.0;
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

int main() {
    int n;
    cout << "Enter the number of players: ";
    cin >> n;

    vector<Player> players(n);
    for (int i = 0; i < n; ++i) {
        cout << "Enter name of player " << i + 1 << ": ";
        cin >> players[i].name;
    }

    // Khởi tạo bộ bài và xáo bài
    vector<Card> deck = createDeck();
    shuffleDeck(deck);

    int deckIndex = 0;

    // Chia bài cho từng người chơi
    for (int i = 0; i < n; ++i) {
        dealHand(deck, players[i], deckIndex);
    }

    // Hiển thị bài của từng người chơi
    for (int i = 0; i < n; ++i) {
        cout << players[i].name << "'s hand:" << endl;
        displayHand(players[i].hand);
        cout << endl;
    }

    // Tìm người thắng
    Player* winner = &players[0];
    bool tie = false;

    for (int i = 1; i < n; ++i) {
        int result = compareHands(*winner, players[i]);
        if (result == -1) {
            winner = &players[i];  // Cập nhật người thắng
            tie = false;
        } else if (result == 0) {
            tie = true;  // Trường hợp hòa
        }
    }

    if (!tie) {
        cout << winner->name << " wins!" << endl;
        winner->wins++;
    } else {
        cout << "It's a tie!" << endl;
        for (int i = 0; i < n; ++i) {
            players[i].draws++;
        }
    }

    // Hiển thị thông tin của từng người chơi
    cout << endl << "Statistics:" << endl;
    for (const auto& player : players) {
        displayPlayerStats(player);
        cout << endl;
    }

    return 0;
}


