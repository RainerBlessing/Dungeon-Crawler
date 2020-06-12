#include "pch.h"
#include "Dungeon.h"

Dungeon::Dungeon(Player p)
{
	this->player = p;
}

int Dungeon::runDungeon()
{
	cout << "Welcome to the dungeon! Inside you will find treasure, but also fierce enemies. Enter at your peril!" << endl;

	player.currentRoom = &rooms[0];
	player.previousRoom = &rooms[0];

	while (true) {
		enterRoom(player.currentRoom);

		if (player.checkIsDead()) {
			//lose the game
			cout << "Game over! Try agein?" << endl;
			return performEndGameLogic();
		}
		else {
			if (player.currentRoom->isExit) {
				if (player.currentRoom->enemies.size() == 0) {
					cout << "You win! Try agein?" << endl;
					return performEndGameLogic();
				}
			}
		}
		cout << "run "<< player.currentRoom << endl;
		handleMovementActions(player.currentRoom);
	}

	return 0;
}

void Dungeon::enterRoom(Room* room)
{
	if (room->enemies.size() != 0) {
		handleRoomWithEnemy(room);
	}
	else if (room->items.size() != 0) {
		handleRoomWithChest(room);
	}
	else {
		handleEmptyRoom(room);
	}
}

void Dungeon::handleEmptyRoom(Room*)
{
	cout << "You enter the room but it is empty." << endl;
	string actions[] = { "a. Move to another room" };
	while (true) {
		printActions(1, actions);
		string input;
		cin >> input;
		if (input == "a") {
			return;
		}
		else {
			cout << "Incorrect choice." << endl;
		}

	}
}

void Dungeon::handleRoomWithChest(Room* room)
{
	cout << "You enter the room and see a large chest." << endl;

	string actions[] = { 
		"a. Loot the chest",
		"b. Move to another room"
	};

	while (true) {
		printActions(1, actions);
		string input;
		cin >> input;
		if (input == "a") {
			handleLootActions(room);
			return;
		}
		else if (input == "b") {
			return;
		}
		else {
			cout << "Incorrect choice." << endl;
		}

	}
}

void Dungeon::handleRoomWithEnemy(Room* room)
{
	GameCharacter enemy = room->enemies.front();

	cout << "You enter the room and see a "<<enemy.name<<"." << endl;

	string actions[] = {
		"a. Fight the "+enemy.name,
		"b. Go back to previous room"
	};

	while (true) {
		printActions(1, actions);
		string input;
		cin >> input;
		if (input == "a") {
			handleFightActions(&enemy);
			return;
		}
		else if (input == "b") {
			player.changeRooms(player.previousRoom);
			enterRoom(player.currentRoom);
			return;
		}
		else {
			cout << "Incorrect choice." << endl;
		}

	}
}

void Dungeon::handleLootActions(Room* room)
{
	Item item = room->items.front();
	int size= room->items.size();


	player.lootRoom(room);
	room->clearLoot();
	for (int i = 0;i < size;i++) {
		// ?
		cout << "You open the chest and find a " << item.name << endl;
		cout << "Your health is now " << player.currentHealth << " Your attack is now " << player.attack << " Your defense is now " << player.defence << endl;
	}	
}

void Dungeon::handleFightActions(GameCharacter* enemy)
{
	string actions[] = {
		"a. Attack ",
		"b. Retreat"
	};

	while (true) {
		printActions(1, actions);
		string input;
		cin >> input;
		//handle player actions
		if (input == "a") {
			int damage = enemy->takeDamage(player.attack);
			cout << "Your attack does " << damage << " damage." << endl;
		}
		else if (input == "b") {
			player.changeRooms(player.previousRoom);
			enterRoom(player.currentRoom);
			return;
		}
		else {
			cout << "Incorrect choice." << endl;
		}

		//check if enemy is dead
		if (enemy -> checkIsDead()) {
			cout << "You killed the " << enemy -> name << "." << endl;
			
			player.increaseStats(10,5,5);
			player.currentRoom->clearEnemies();

			return;
		}

		//handle enemy actions
		int damage = player.takeDamage(enemy -> attack);
		cout << "The "<<enemy->name <<" attacks you and does " << damage << " damage." << endl;
		cout << "Your health is now " << player.currentHealth<< "." << endl;

		if (player.checkIsDead()) {
			cout << "You were killed by the " << enemy -> name << "." << endl;
			return;
		}
	}
}

void Dungeon::handleMovementActions(Room* room)
{
	while (true) {
		if (room->pos == 0) {
			string actions[] = {
				"a. Move right",
				"b. Move down"
			};

			printActions(2, actions);

			string input;
			cin >> input;
			if (input == "a") {
				player.changeRooms(&rooms[1]);
				return;
			}
			else if (input == "b") {
				player.changeRooms(&rooms[2]);
				return;
			}
			else {
				cout << "Incorrect choice." << endl;
			}
		}
		else if (room->pos == 1) {
			string actions[] = {
				"a. Move left"
			};

			printActions(1, actions);

			string input;
			cin >> input;
			if (input == "a") {
				player.changeRooms(&rooms[0]);
				return;
			}
			else {
				cout << "Incorrect choice." << endl;
			}
		}
		else if (room->pos == 2) {
			string actions[] = {
				"a. Move up",
				"b. Move right"
			};

			printActions(2, actions);

			string input;
			cin >> input;
			if (input == "a") {
				player.changeRooms(&rooms[0]);
				return;
			}
			else if (input == "b") {
				player.changeRooms(&rooms[3]);
				return;
			}
			else {
				cout << "Incorrect choice." << endl;
			}
		}
		else {
			string actions[] = {
				"a. Move left"
			};

			printActions(2, actions);

			string input;
			cin >> input;
			if (input == "a") {
				player.changeRooms(&rooms[2]);
				return;
			}
			else {
				cout << "Incorrect choice." << endl;
			}
		}
	}
}

void Dungeon::printActions(int numberOfActions, string actions[])
{
	cout << "Choose an action" << endl;
	for (int i = 0;i < numberOfActions;i++) {
		cout << actions[i] << endl;
	}
}

int Dungeon::performEndGameLogic()
{
	string input;
	string actions[] = { 
		"a. Yes",
		"b. No" 
	};

	while (true) {
		printActions(2, actions);
		cin >> input;
		if (input == "a") {
			return 1;
		}
		else if (input == "b") {
			return 0;
		}
		else {
			cout << "Incorrect choice." << endl;
		}
	}	
}
