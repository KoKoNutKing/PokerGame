#include <iostream>

using namespace std;

enum class Suits {
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES
};

enum class Ranks {
    ACE = 1,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING
};

struct Card {
    Ranks rank;
    Suits suit;

 void PrintCard() {
        PrintRank();

        cout << " of ";

        PrintSuit();

        cout << std::endl;
    }
    
    void PrintRank() {
        if (rank == Ranks::JACK) {
            cout << "jack";
        }
        else if (rank == Ranks::QUEEN) {
            cout << "queen";
        }
        else if (rank == Ranks::KING) {
            cout << "king";
        }
        else if (rank == Ranks::ACE) {
            cout << "ace";
        }
        else {
            cout << (int)rank;
        }
    }

    void PrintSuit() {
        if (suit == Suits::CLUBS) {
            cout << "clubs";
        }
        else if (suit == Suits::DIAMONDS) {
            cout << "diamonds";
        }
        else if (suit == Suits::HEARTS) {
            cout << "hearts";
        }
        else if (suit == Suits::SPADES) {
            cout << "spades";
        }
    }
};


struct Deck {
    Card arrCards[52];
    int index;

    void PrintDeck() {
        for (int col = (int)Suits::CLUBS; col <= (int)Suits::SPADES; col++) {
            for (int row = (int)Ranks::ACE; row <= (int)Ranks::KING; row++) {
                index = col*13 + row - 1;
                arrCards[index].PrintCard();
            }
        }
    }

    void SetupCards() {
        for (int col = (int)Suits::CLUBS; col <= (int)Suits::SPADES; col++) {
            for (int row = (int)Ranks::ACE; row <= (int)Ranks::KING; row++) {
                Card c;
                c.suit = (Suits)col;
                c.rank = (Ranks)row;
                index = col*13 + row - 1;
                arrCards[index] = c;
            }
        }
        
    }
};



int main() {
    Deck deck;
    deck.SetupCards();
    deck.PrintDeck();
}