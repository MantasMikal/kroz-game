#ifndef CONSUMABLE_H
#define CONSUMABLE_H

#include "Item.h"

class Consumable :
	public Item
{
public:
	Consumable(int healthBoost = 0, int attackBoost = 0, int defenceBoost = 0,
		string name = "NONE", string rarity = "NONE", int value = 0, int id = 0);
	~Consumable();

	//Pure virtual functions

	virtual Consumable* clone()const;
	virtual ItemType itemType()const;

	//Virtual functions

	virtual int getHealthBoost() { return this->healthBoost; }
	virtual int getDefenceBoost() { return this->defenceBoost; }
	virtual int getAttackBoost() { return this->attackBoost; }

	//Mutators

private:
	int healthBoost;
	int defenceBoost;
	int attackBoost;;
};

#endif