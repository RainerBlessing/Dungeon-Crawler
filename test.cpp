#include "pch.h"
#include "Item.h"
#include "GameCharacter.h"
#include "Room.h"
#include "Player.h"

TEST(Item, SetupParameters) {
  Item i = Item("test", 1, 2, 3);
  EXPECT_EQ(i.name,"test");
  EXPECT_EQ(i.health,1);
  EXPECT_EQ(i.attack,2);
  EXPECT_EQ(i.defence,3);
}


TEST(GameCharacter, SetupParameters) {
	GameCharacter i = GameCharacter("test", 1, 2, 3);
	EXPECT_EQ(i.name, "test");
	EXPECT_EQ(i.health, 1);
	EXPECT_EQ(i.attack, 2);
	EXPECT_EQ(i.defence, 3);
}

TEST(GameCharacter, TakeDamage) {
	GameCharacter i = GameCharacter("test", 10, 2, 3);
	
	//Player survives
	EXPECT_EQ(i.takeDamage(5),2);
	EXPECT_EQ(i.currentHealth,8);
	EXPECT_EQ(i.checkIsDead(), false);

	//Player dies
	EXPECT_EQ(i.takeDamage(20),17);
	EXPECT_EQ(i.currentHealth, 0);
	EXPECT_EQ(i.checkIsDead(), true);
}

TEST(Room, SetupParameters) {
	vector<Item> items;
	vector<GameCharacter> enemies;

	Room r = Room(0, true, items
		, enemies);	
}

TEST(Player, LootRoom) {
	vector<Item> items;
	Item i = Item("item", 1, 2, 3);
	items.push_back(i);
	vector<GameCharacter> enemies;

	Room r = Room(0, true, items, enemies);

	Player p = Player("player", 10, 2, 3);

	p.lootRoom(&r);

	EXPECT_EQ(p.inventory.size(), 1);
	EXPECT_EQ(r.items.size(), 0);
}