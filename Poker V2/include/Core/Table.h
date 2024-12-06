#pragma once

#include <vector>
#include "Player.h" // Assuming you already have a Player class

class Player;
// Structure to represent a Slot on the table
struct Slot {
    int x, y;              
    Player* player = nullptr;
};

class Table {   
public:
    Table(std::vector<Slot> &gamemodeSlots);
    ~Table();

    void addPlayer(Player* player, int slotIndex);
    SDL_Point getSlotPosition(int slotIndex) const;
    void render(SDL_Renderer* renderer);

private:
    std::vector<Slot> slots; 
};
