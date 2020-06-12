#include "pch.h"
#include "PLayer.h"

void Player::addItem(Item item)
{
	inventory.push_back(item);
}

void Player::increaseStats(int currentHealth, int attack, int defense)
{
	this->currentHealth += currentHealth;
	this->attack += attack;
	this->defence += defense;
}

void Player::lootRoom(Room* room)
{
	inventory = room->items;
	room->clearLoot();
}

void Player::changeRooms(Room* room)
{
	cout << room->pos << endl;
	this->previousRoom = this->currentRoom;
	this->currentRoom = room;
}
