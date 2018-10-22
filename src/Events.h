
#include "Player.h"
#include "Monster.h"
#include "DB.h"

class Events {
private:


public:
	Events();


	bool generateRandomEvent(Player &player);
	bool generateTownEvent();

	bool monsterEncounterEvent(Player &player);
	bool shopEncounterEvent(Player &player);
	bool givePlayerLoot(Player &player);

	// ALL EVENTS CAN BE CREATED WITH FUNCTIONS. Then, use generateTownEvent() to
	// randomly pick an event and show it to the user to deal with. e.g.: 
	// After every step of the player, call generateMapEvent()
	// This means that this class should be connected with Inventory, Monsters, Shop classese
};