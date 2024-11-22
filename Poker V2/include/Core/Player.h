#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <map>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Core/TextureManager.h"
#include "Core/Card.h"
#include "Card.h"

class Card;

class Player {
public:
    // Constructor and Destructor
    Player(SDL_Renderer* renderer, const std::string& texturePath, int x, int y);
    ~Player();

    // Update and Render methods
    void update();
    void render(SDL_Renderer* renderer);


    void setName(const std::string& input);
    // Getter and Setter for position
    void setPosition(int x, int y);
    SDL_Point getPosition() const;

    void addCard(const Card &card);
    void sortHand();
    void renderHand(SDL_Renderer* renderer);
    std::pair<int, int> evaluateHand() const;

    // Manage Score
    // void addScore(int points);
    // int getScore() const;

private:
    std::string name;      // Player name
    std::vector<Card> hand;
    int x, y;              // Player position

    // int score;             // Player score
    SDL_Renderer* renderer;
    SDL_Texture* playerTexture;  // Texture for rendering
    SDL_Rect srcRect;      // Source rectangle for sprite
    SDL_Rect destRect;     // Destination rectangle for rendering
};
