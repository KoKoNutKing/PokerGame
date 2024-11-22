#include "Core/Basic.h"

Basic::Basic(SDL_Renderer* renderer, TTF_Font* font, SDL_Event& event)
    : renderer(renderer), font(font), event(event), table(table), deck(deck), numberOfPlayers(2), phrase(NUMBER) {

    // Initialize input boxes and buttons
    playerNumberBox = new TextBox(100, 100, 200, 50, font, renderer);  // Box for number of players
    addPlayerButton = new Button(renderer, 350, 100, 50, 50, "+", font); // Increase button
    subPlayerButton = new Button(renderer, 50, 100, 50, 50, "-", font); // Decrease button
    nextButton = new Button(renderer, 200, 200, 100, 50, "Next", font); // Next button
    startButton = new Button(renderer, 200, 300, 100, 50, "Start", font); // Start button
}

Basic::~Basic() {
    // Cleanup dynamically allocated memory
    delete playerNumberBox;
    for (auto& box : playerNameBoxes) {
        delete box;
    }

    delete addPlayerButton;
    delete subPlayerButton;
    delete nextButton;
    delete startButton;
}

void Basic::initBasic() {
    // Initialize slots and other components
    basicSlots = {
        {100, 200, nullptr}, {300, 200, nullptr}, {500, 200, nullptr}, {700, 200, nullptr}, {900, 200, nullptr}
    };
    *table = Table(basicSlots);
    deck->createDeck();
}
void Basic::update() {
    if (phrase == INIT_PLAYER) {
        playerNameBoxes.clear();
        for (int i = 0; i < numberOfPlayers; ++i) {
            playerNameBoxes.push_back(new InputBox(100, 200 + (i * 60), 200, 50, font, renderer));
        }
        phrase = PLAYER;
    }
}

void Basic::render() {
    switch (phrase)
    {
    case NUMBER:
        playerNumberBox->render();   
        addPlayerButton->render();   
        subPlayerButton->render();   
        nextButton->render();
        break;
    case PLAYER:
        for (auto& box : playerNameBoxes) {
            box->render();
        }
        startButton->render();
        break;
    case START:
        // Handle start button click
        // table->render(renderer);
        std::cout << "hi";
        break;
    default:
        break;
    }
}

void Basic::getPlayer(const std::string& name) {
    if (!name.empty()) {
        Player newPlayer(renderer, "resrc\\avatar.png", 25, 25);
        newPlayer.setName(name);
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
            if (nextButton->isClicked(event.button.x, event.button.y)) {
                phrase = INIT_PLAYER;
            }
        }
        break;
    case PLAYER:
        for (int i = 0; i < numberOfPlayers; ++i) {
            std::string input;
            playerNameBoxes[i]->handleEvents(event, input);
        }
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (startButton->isClicked(event.button.x, event.button.y)) {
                phrase = START;
            }
        }
        break;
    case START:
    // Handle start button click
        break;
    default:
        break;
    }


}

void Basic::start() {

}