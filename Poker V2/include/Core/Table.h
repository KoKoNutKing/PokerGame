#pragma once

#include <vector>
#include "Player.h" // Assuming you already have a Player class

class Player;
// Structure to represent a Slot on the table
struct Slot {
    int x, y;               // Coordinates for the slot
    Player* player = nullptr; // Pointer to a Player occupying the slot
};

class Table {   
public:
    Table(std::vector<Slot> &gamemodeSlots);
    ~Table();

    // Add a player to a specific slot
    void addPlayer(Player* player, int slotIndex);

    // Get the position of a specific slot
    SDL_Point getSlotPosition(int slotIndex) const;

    // Render all players on the table
    void render(SDL_Renderer* renderer);

private:
    std::vector<Slot> slots; 
};
