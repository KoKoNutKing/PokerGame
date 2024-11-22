#include "Core/Table.h"
#include <iostream>

Table::Table(std::vector<Slot> &gamemodeSlots) {
    slots = gamemodeSlots;
}

Table::~Table() {
    // The table itself doesn't own players, so no need to delete them here
}

void Table::addPlayer(Player* player, int slotIndex) {
    if (slotIndex < 0 || slotIndex >= slots.size()) {
        std::cerr << "Invalid slot index: " << slotIndex << std::endl;
        return;
    }
    slots[slotIndex].player = player;
}


void Table::render(SDL_Renderer* renderer) {
    for (const Slot& slot : slots) {
        if (slot.player) {
            slot.player->setPosition(slot.x, slot.y); // Update player position
            slot.player->render(renderer);           // Render the player
        }
    }
}