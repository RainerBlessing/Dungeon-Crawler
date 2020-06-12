#pragma once
#include "GameCharacter.h"
#include "Room.h"

class Player :
    public GameCharacter
{
public:
    using GameCharacter::GameCharacter;

    Room* currentRoom;
    Room* previousRoom;
    vector<Item> inventory;
    void addItem(Item);
    void increaseStats(int, int, int);
    void lootRoom(Room*);
    void changeRooms(Room*);
};

