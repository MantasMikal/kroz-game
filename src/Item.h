#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <iomanip>
#include <string>
#include <array>

using namespace std;

enum class ItemType { Weapon, Armor, Consumable }; //types of items --- TODO add more items

class Item
{

private:
	string name;
	string rarity;
	int value;
	int ID;

public:

	//TODO
	//add upgrade item functions 
		//weapons increase attack ? 
		//armor increase defence?
		//allow the player to have greater control

	Item(string name = "NONE", string rarity = "NONE", int value = 0, int id = 0);
	virtual ~Item();

	//Pure virtual functions

	virtual ItemType itemType()const = 0;
	virtual Item* clone()const = 0;

	//Consumable virtual functions

	virtual int getHealthBoost() { return 0; }
	virtual int getDefenceBoost() { return 0; }
	virtual int getAttackBoost() { return 0; }

	//Armor virtual functions

	virtual int getArmorType() { return -1; }

	//Weapon virtual functions

	virtual int getWeaponType() { return -1; }

	//Weapon and Armor virtual functions
	virtual int getDefence() { return 0; }
	virtual int getAttack() { return 0; }
	virtual int getStrength() { return 0; }
	virtual int getLuck() { return 0; }
	virtual int getLvlReq() { return 1; }


	//Accessors
	const string& getName() const { return this->name; }
	const string& getRarity() const { return this->rarity; }
	const int& getValue() const { return this->value; }
	const int& getID() const { return this->ID; }


};

#endif
