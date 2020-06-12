#include "pch.h"
#include "Item.h"

Item::Item(string name, int health, int attack,int defence)
{
	this->name = name;
	this->health = health;
	this->currentHealth = health;
	this->attack = attack;
	this->defence = defence;
}
