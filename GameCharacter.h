#pragma once
#include "Item.h"

class GameCharacter :  public Item
{
public:
	using Item::Item;

	int takeDamage(int amount);
	bool checkIsDead() { return currentHealth == 0; }
};

