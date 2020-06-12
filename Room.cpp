#include "pch.h"
#include "Room.h"

Room::Room(int pos, bool isExit, vector<Item> items, vector<GameCharacter> enemies)
{
	this->pos = pos;
	this->isExit = isExit;
	this->items = items;
	this->enemies = enemies;
}

void Room::clearLoot()
{
	this->items.clear();
}

void Room::clearEnemies()
{
	this->enemies.clear();
}
