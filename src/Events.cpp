#include "Events.h"
#include <iostream>
#include <string>
#include <array>


Events::Events() {
}

bool Events::generateRandomEvent(Player& player) {
	/* initialize random seed: */
	srand(time(NULL));
	int seed = rand() % 3 + 1;
	switch (seed)
	{
	default:
		break;
	case 1:
		this->monsterEncounterEvent(player);
		break;
	case 2:
		this->givePlayerLoot(player);
		break;
	case 3:
		this->shopEncounterEvent(player);
		break;
	}

	return true;
}

bool Events::generateTownEvent() {

	//PICK RANDOM EVENT FROM POOL OF EVENTS

	return true;
}

bool Events::monsterEncounterEvent(Player &player) {
	//Create RANDOM monster
	//monster class or game class should have fighting implemented
	DB::getInstance()->getItemType(1);
	//initialise random seed to create random monster
	srand(time(NULL));
	int monsterLevel = rand() % player.getLVL() + 2;

	// create monster with a level. minimum level is the player's level.
	Monster monster(monsterLevel);
	DB::getInstance()->loadMonsterData(monster);
	monster.setValues();

	std::cout << "\n You have found a " << monster.getName() << "! \n";
	std::cout << monster.printHealth() << endl;
	player.battleOptions(monster);
	
	if (player.getCurrentHealth() <= 0) {
		std::cout << "You dead boi..." << endl;
        std::cout << "But a dark wizard rewinds time around you" << endl;
        std::cout << "and brings you back to life. Your body feels weak." << endl;
        
        std::string username = player.getUsername();
        std::string password = player.getPassword();
        DB::getInstance()->loadPlayerData(player, username, password);
        player.setCurrentHealth(player.getMaxHealth() * 0.5);
        
		return false;
	}
    else if (monster.currentHealth <= 0) {
		givePlayerLoot(player);
        player.setXP(player.getXP() + monster.getXP());
		std::cout << "You have gained " << monster.getXP() << " XP!\n\n";
	}
	return true;
}

bool Events::givePlayerLoot(Player &player)
{
	std::string itemTypes[3] = { "Weapon", "Armor", "Consumable" };
	srand(time(NULL));
	int itemIndex = rand() % 3;

	std::cout << "\x1B[2J\x1B[H";
	std::cout << R"(
                        ____...------------...____
               _.-"` /o/__ ____ __ __  __ \o\_`"-._
             .'     / /                    \ \     '.
             |=====/o/======================\o\=====|
             |____/_/________..____..________\_\____|
             /   _/ \_     <_o#\__/#o_>     _/ \_   \
             \_________\####/_________/
              |===\!/========================\!/===|
              |   |=|          .---.         |=|   |
              |===|o|=========/     \========|o|===|
              |   | |         \() ()/        | |   |
              |===|o|======{'-.) A (.-'}=====|o|===|
              | __/ \__     '-.\uuu/.-'    __/ \__ |
              |==== .'.'^'.'.====|
              |  _\o/   __  {.' __  '.} _   _\o/  _|
              `""""-""""""""""""""""""""""""""-""""`
    )" << std::endl << std::endl;
	DB::getInstance()->loadRandomItemData(player, itemTypes[itemIndex]);
	return true;
}


bool Events::shopEncounterEvent(Player &player) {
	Shop shop;
	DB::getInstance()->loadShopRandomWeaponData(shop, player);
	DB::getInstance()->loadShopRandomArmorData(shop, player);
	DB::getInstance()->loadShopRandomConsumableData(shop, player);
	while (!shop.getIsFinished()) { shop.showShopOptions(player); } //Passing Player up the chain to the Shop class, where buy/sell logic is taken care of
	return true;
}