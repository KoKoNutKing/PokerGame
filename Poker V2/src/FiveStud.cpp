#include "Core/FiveStud.h"

FiveStud::FiveStud(SDL_Renderer* renderer, TTF_Font* font, SDL_Event& event)
    : renderer(renderer), font(font), event(event), table(nullptr), deck(nullptr), numberOfPlayers(2), phrase(NUMBER1) {


    // Initialize input boxes and buttons
    playerNumberBox = new TextBox(Config::getPlayerNumButtonX, Config::getPlayerNumButtonY, Config::getPlayerNumButtonWidth, Config::getPlayerNumButtonHeight, font, renderer);  // Box for number of players
    addPlayerButton = new Button(renderer, Config::addPlayerButtonX, Config::addPlayerButtonY, Config::addPlayerButtonWidth, Config::addPlayerButtonHeight, "+", font); // Increase button
    subPlayerButton = new Button(renderer, Config::subPlayerButtonX, Config::subPlayerButtonY, Config::subPlayerButtonWidth, Config::subPlayerButtonHeight, "-", font); // Decrease button
    getPlayerNumButton = new Button(renderer, Config::getPlayerNumButtonX, Config::getPlayerNumButtonY + 100, Config::getPlayerNumButtonWidth, Config::getPlayerNumButtonHeight, "Next", font); // Next button
    getPlayerNameButton = new Button(renderer, Config::midButtonX, Config::midButtonY, Config::midButtonWidth, Config::midButtonHeight, "Next", font); // Start button
    startButton = new Button(renderer, Config::startButtonX, Config::startButtonY, Config::startButtonWidth, Config::startButtonHeight, "Start", font); // Start button

    resultBox = new TextBox(Config::startButtonX, Config::ScreenHeight / 2, 200, 50, font, renderer);

}

FiveStud::~FiveStud() {
    // Cleanup dynamically allocated memory
    delete playerNumberBox;
    for (auto& box : playerNameBoxes) {
        delete box;
    }
    playerNameBoxes.clear();

    

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



void FiveStud::initFiveStud() {
    fiveStudSlots = {
        {50, 50, nullptr}, {50, 175, nullptr}, {50, 300, nullptr}, {50, 425, nullptr}, {50, 550, nullptr}
    };
    
    //background
    FiveStudGetPlBg = TextureManager::LoadTexture(Config::BasicGetPlPath, renderer);
    FiveStudGetNumBg = TextureManager::LoadTexture(Config::BasicGetNumPath, renderer);
    FiveStudPlayingBg = TextureManager::LoadTexture(Config::BasicPlayingPath, renderer);


    if (table) {
        delete table; 
    }
    players = {};
    table = new Table(fiveStudSlots); 
    deck = new Deck(renderer);
    deck->createDeck();

    
}
void FiveStud::update() {

}

void FiveStud::render() {
    switch (phrase)
    {
    case NUMBER:
        TextureManager::DrawTexture(FiveStudGetNumBg, renderer, Config::BgSrcRect, Config::BgDestRect);
        playerNumberBox->render();   
        addPlayerButton->render();   
        subPlayerButton->render();   
        getPlayerNumButton->render();
        break;
    case PLAYER:
        TextureManager::DrawTexture(FiveStudGetPlBg, renderer, Config::BgSrcRect, Config::BgDestRect);
        for (auto& playerBox : playerNameBoxes) {
            playerBox->render();
        }
        getPlayerNameButton->render();
        break;
    case START:
        // Handle start button click
        TextureManager::DrawTexture(FiveStudPlayingBg, renderer, Config::BgSrcRect, Config::BgDestRect);

        startButton->render();
        table->render(renderer);
        for (auto & box : playerNameDrawer) {
            box->render();
        }
        renderSharedCard();
        resultBox->render();
        break;
    default:
        break;
    }
}

void FiveStud::getPlayer(const std::string& name) {
    if (!name.empty()) {
        Player* newPlayer = new Player(renderer, Config::DefaultAva, 25, 25);
        newPlayer->setName(name);
        players.push_back(newPlayer);
    }
}

void FiveStud::handleInput() {
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
                phrase = PLAYER1;
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
                phrase = START1;
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
void FiveStud::dealHand(Deck& deck, Player* player, int& deckIndex) {
    const int handSize = 2; // Number of cards to deal
    for (int i = 0; i < handSize; ++i) {
        Card* card = deck.drawCard(deckIndex);
        if (card) {
            // Use the card
            player->addCard(*card);
            deckIndex++;
        } else {
            std::cerr << "Error: Card draw failed!" << std::endl; //debug
        }
    }
}


int FiveStud::compareHands(const Player& p1, const Player& p2) {
    Player tmp1 = p1;
    Player tmp2 = p2;
    for (int i = 0; i < 3; ++i) {
        tmp1.addCard(sharedCard[i]);
        tmp2.addCard(sharedCard[i]);
    }
    std::pair<int, int> hand1 = tmp1.evaluateHand();
    std::pair<int, int> hand2 = tmp2.evaluateHand();
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

void FiveStud::renderSharedCard() {
        for (int i = 0; i < sharedCard.size(); ++i) {
        sharedCard[i].update(Config::ScreenWidth / 2 - 150 + 150 * i, Config::ScreenHeight / 2); // may change
        sharedCard[i].render();
    }
}


void FiveStud::determineAndDisplayWinner() {
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

void FiveStud::start() {
    sharedCard.clear();
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
    
    for (int i = 0; i < 3; ++i) {
        Card* card = deck->drawCard(deckIndex);
        if (card) {
            // Use the card
            sharedCard.push_back(*card);
            deckIndex++;
        } else {
            std::cerr << "Error: Card draw failed!" << std::endl; //debug
        }
    }

    for (auto& player : players) {
        if (player) {
            dealHand(*deck, player, deckIndex);
        } else {
            std::cerr << "Player is null!" << std::endl; //debug
        }
    }

    determineAndDisplayWinner();
}

void FiveStud::addNameBox() {
    playerNameBoxes.clear();
    for (int i = 0; i < numberOfPlayers; ++i) {
        playerNameBoxes.push_back(new InputBox(Config::ScreenWidth / 2 - 100, 200 + (i * 60), 200, 50, font, renderer));
        playerNameDrawer.push_back(new TextBox(50, fiveStudSlots[i].y + 100, 200, 50, font, renderer));

    }
    phrase = PLAYER1;
    
}

void FiveStud::createTable() {
    dataSaver.clear();
    if (table == nullptr) {
        table = new Table(fiveStudSlots);
    }

    for (int i = 0; i < numberOfPlayers; ++i) {
        getPlayer(playerNameBoxes[i]->getText());
        playerNameDrawer[i]->setText(playerNameBoxes[i]->getText());
        table->addPlayer(players[i], i); // Add each player to the table

        dataSaver.push_back(PlayerData {playerNameBoxes[i]->getText(), 0, 0}); //
        
    }
}

void FiveStud::updateData(std::vector<PlayerData> &data, std::string winnerName) {
    for (auto & player: data) {
        if (player.name == winnerName) {
            player.totalFiveWins += 1;
            }
        player.totalFive += 1;
    }
}