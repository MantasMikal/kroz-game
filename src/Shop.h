/* Shop class. We are talking with this object trough Events class */


#include "Item.h"
#include "Weapon.h"
#include "Armor.h"
#include "Consumable.h"
#include "Player.h"
#include <vector>

class Shop {
private:
	array<Armor, 10> equipment;
	array<Weapon, 10> weapons;
	array<Consumable, 10> consumables;
	bool isFinished = false;

	// WE CAN PULL SOME RANDOM ITEMS FROM DATABASE AND HAVE THEM HERE...


public:
	Shop();

	void printWeapons();
	void printArmor();
	void printConsumables();
	Armor getArmor(int index);
	Weapon getWeapon(int index);
	Consumable getConsumable(int index);

	void addArmor(Armor armor);
	void addWeapon(Weapon weapon);
	void addConsumable(Consumable consumable);

	void generateItems(); //Generate items by level or jus have them static?
	int showShopOptions(Player &player); // 1.0 Buy or Sell? 1.1 Which item group? 2. exit
	bool buyWeapon(Player &player, int index);
	bool buyArmor(Player &player, int index);
	bool buyConsumable(Player &player, int index);

	bool getIsFinished();
	void setIsFinished(bool val);


	bool sell(Player &player, int index);
	void displayLogo();



};