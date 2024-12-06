#include "Core/Table.h"
#include <iostream>

Table::Table(std::vector<Slot> &gamemodeSlots) {
    slots = gamemodeSlots;
}

Table::~Table() {
    for (Slot& slot : slots) {
        delete slot.player; // Free owned players
        slot.player = nullptr;
    }
}

void Table::addPlayer(Player* player, int slotIndex) {
    if (slotIndex < 0 || slotIndex >= slots.size()) {
        std::cerr << "Invalid slot index: " << slotIndex << std::endl;
        return;
    }
    player->setPosition(slots[slotIndex].x, slots[slotIndex].y); // Update player position
    slots[slotIndex].player = player;
}


void Table::render(SDL_Renderer* renderer) {
    for (const Slot& slot : slots) {
        if (slot.player) {            
            slot.player->setAvatar(Config::DefaultAva);
            slot.player->render(renderer);    
            slot.player->renderHand(renderer); // Render the player
        }
    }
}
