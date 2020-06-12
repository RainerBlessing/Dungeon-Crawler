#pragma once
#include <string>

using namespace std;

class Item
{
public:
	string name;
	int health, currentHealth, attack, defence;
	Item(string="", int=10, int=1, int=1);
};

