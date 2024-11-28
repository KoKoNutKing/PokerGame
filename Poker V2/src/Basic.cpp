#include "Core/Basic.h"

Basic::Basic(SDL_Renderer* renderer, TTF_Font* font, SDL_Event& event)
    : renderer(renderer), font(font), event(event), table(nullptr), deck(nullptr), numberOfPlayers(2), phrase(NUMBER) {


    // Initialize input boxes and buttons
    playerNumberBox = new TextBox(Config::getPlayerNumButtonX, Config::getPlayerNumButtonY, Config::getPlayerNumButtonWidth, Config::getPlayerNumButtonHeight, font, renderer);  // Box for number of players
    addPlayerButton = new Button(renderer, Config::addPlayerButtonX, Config::addPlayerButtonY, Config::addPlayerButtonWidth, Config::addPlayerButtonHeight, "+", font); // Increase button
    subPlayerButton = new Button(renderer, Config::subPlayerButtonX, Config::subPlayerButtonY, Config::subPlayerButtonWidth, Config::subPlayerButtonHeight, "-", font); // Decrease button
    getPlayerNumButton = new Button(renderer, Config::getPlayerNumButtonX, Config::getPlayerNumButtonY + 100, Config::getPlayerNumButtonWidth, Config::getPlayerNumButtonHeight, "Next", font); // Next button
    getPlayerNameButton = new Button(renderer, 200, 300, 100, 50, "Next", font); // Start button
    startButton = new Button(renderer, Config::startButtonX, Config::startButtonY, Config::startButtonWidth, Config::startButtonHeight, "Start", font); // Start button

    resultBox = new TextBox(500, 500, 200, 50, font, renderer);  

}

Basic::~Basic() {
    // Cleanup dynamically allocated memory
    delete playerNumberBox;
    for (auto& box : playerNameBoxes) {
        delete box;
    }

    for (auto& player : players) {
        delete player;
    }

    delete deck;
    delete addPlayerButton;
    delete subPlayerButton;
    delete getPlayerNumButton;
    delete getPlayerNameButton;
    delete startButton;
}



void Basic::initBasic() {
    // Initialize slots and other components
    basicSlots = {
        {100, 100, nullptr}, {100, 200, nullptr}, {100, 300, nullptr}, {100, 400, nullptr}, {100, 500, nullptr}
    };
    //background
    BasicGetPlBg = TextureManager::LoadTexture(Config::BasicGetPlPath, renderer);
    BasicPlayingBg = TextureManager::LoadTexture(Config::BasicPlayingPath, renderer);

    if (table) {
        delete table; // Clean up any existing table
    }
    players = {};
    table = new Table(basicSlots); 
    deck = new Deck(renderer);
    deck->createDeck();



    
}
void Basic::update() {

}

void Basic::render() {
    switch (phrase)
    {
    case NUMBER:
        TextureManager::DrawTexture(BasicGetPlBg, renderer, Config::BgSrcRect, Config::BgDestRect);
        playerNumberBox->render();   
        addPlayerButton->render();   
        subPlayerButton->render();   
        getPlayerNumButton->render();
        break;
    case PLAYER:
        TextureManager::DrawTexture(BasicGetPlBg, renderer, Config::BgSrcRect, Config::BgDestRect);
        for (auto& box : playerNameBoxes) {
            box->render();
        }
        getPlayerNameButton->render();
        break;
    case START:
        // Handle start button click
        TextureManager::DrawTexture(BasicPlayingBg, renderer, Config::BgSrcRect, Config::BgDestRect);

        startButton->render();
        table->render(renderer);
        resultBox->render();
        break;
    default:
        break;
    }
}

void Basic::getPlayer(const std::string& name) {
    if (!name.empty()) {
        Player* newPlayer = new Player(renderer, "resrc\\avatar.png", 25, 25);
        newPlayer->setName(name);
        players.push_back(newPlayer);
    }
}

void Basic::handleInput() {
    // Handle input for number of players
    switch (phrase)
    {
    case NUMBER:
         // Handle player number increment and decrement
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (addPlayerButton->isClicked(event.button.x, event.button.y)) {
                numberOfPlayers = std::min(numberOfPlayers + 1, 5);  // Max of 5 players
            } else if (subPlayerButton->isClicked(event.button.x, event.button.y)) {
                numberOfPlayers = std::max(numberOfPlayers - 1, 2);  // Min of 2 players
            }
            playerNumberBox->setText(std::to_string(numberOfPlayers));
            if (getPlayerNumButton->isClicked(event.button.x, event.button.y)) {
                addNameBox();
                phrase = PLAYER;
            }
        }
        break;
    case PLAYER:
        for (int i = 0; i < numberOfPlayers; ++i) {
            std::string input;
            playerNameBoxes[i]->handleEvents(event);
        }
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (getPlayerNameButton->isClicked(event.button.x, event.button.y)) {
                createTable();
                phrase = START;
            }
        }
        break;
    case START:
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (startButton->isClicked(event.button.x, event.button.y)) {
                start();
            }
        }        
        break;
    default:
        break;
    }


}

//game rule
void Basic::dealHand(Deck& deck, Player* player, int& deckIndex) {
    const int handSize = 5; // Number of cards to deal
    for (int i = 0; i < handSize; ++i) {
        Card* card = deck.drawCard(deckIndex);
        //Card* card = new Card(renderer, 0, 0, DIAMONDS, THREE);
        if (card) {
            // Use the card
            player->addCard(*card);
            deckIndex++;
        } else {
            std::cerr << "Error: Card draw failed!" << std::endl; //debug
        }
    }
}


int Basic::compareHands(const Player& p1, const Player& p2) {
    std::pair<int, int> hand1 = p1.evaluateHand();
    std::pair<int, int> hand2 = p2.evaluateHand();
    if (hand1.first > hand2.first) {
        return 1;
    }
    if (hand1.first < hand2.first) {
        return -1;
    }

    if (hand1.second > hand2.second) {
        return 1;
    }
    if (hand1.second < hand2.second) {
        return -1;
    }
    return 0;
}

void Basic::determineAndDisplayWinner() {
    Player* winner = players[0];
    bool tie = false;

    for (auto& player : players) {
        int result = compareHands(*winner, *player);
        if (result == -1) {
            winner = player;
            tie = false;
        } else if (result == 0 && winner != player) {
            tie = true;
        }
    }
    updateData(dataSaver, winner->getName());

    std::string resultMessage;
    if (tie) {
        resultMessage = "It's a tie!";
    } else {
        resultMessage = winner->getName() + " wins!";
    }

    resultBox->setText(resultMessage);
}

void Basic::start() {
    for (auto& player : players) {
        if (player) {
            player->resetHand();
        } else {
            std::cerr << "Player is null!" << std::endl; //debug
        }
    }

     if (!deck) {
        std::cerr << "Deck is not initialized!" << std::endl; //debug
        return;
    }

    if (players.empty()) {
        std::cerr << "No players have been created!" << std::endl; //debug
        return;
    }
    deck->shuffleDeck();
    int deckIndex = 0;
    
    for (auto& player : players) {
        if (player) {
            dealHand(*deck, player, deckIndex);
        } else {
            std::cerr << "Player is null!" << std::endl; //debug
        }
    }

    determineAndDisplayWinner();
}

void Basic::addNameBox() {
    playerNameBoxes.clear();
    for (int i = 0; i < numberOfPlayers; ++i) {
        playerNameBoxes.push_back(new InputBox(100, 200 + (i * 60), 200, 50, font, renderer));
    }
    phrase = PLAYER;
    
}

void Basic::createTable() {
    dataSaver.clear();
    if (table == nullptr) {
        table = new Table(basicSlots);
    }

    for (int i = 0; i < numberOfPlayers; ++i) {
        getPlayer(playerNameBoxes[i]->getText());
        table->addPlayer(players[i], i); // Add each player to the table

        dataSaver.push_back(PlayerData {playerNameBoxes[i]->getText(), 0, 0}); //
        
    }
}

void Basic::updateData(std::vector<PlayerData> &data, std::string winnerName) {
    for (auto & player: data) {
        if (player.name == winnerName) {
            player.totalBasicWins += 1;
            }
        player.totalBasic += 1;
    }
}