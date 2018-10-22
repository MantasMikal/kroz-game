#ifndef ARMOR_H
#define ARMOR_H

#include "Item.h"

class Armor :
	public Item
{
public:

	Armor(int armorType = -1, int lvlReq = 1, int defence = 0, int attack = 0, int strength = 0, int luck = 0,
		string name = "NONE", string rarity = "NONE", int value = 0, int id = 0);
	~Armor();

	//pure virtual functions

	virtual Armor* clone()const;
	virtual ItemType itemType()const;

	//virtual functions

	virtual int getDefence() { return this->defence; }
	virtual int getAttack() { return this->attack; }
	virtual int getStrength() { return this->strength; }
	virtual int getLuck() { return this->luck; }

	virtual int getArmorType() { return this->armorType; }
	virtual int getLvlReq() { return this->lvlReq; }

	//mutators

	void setDefence(int n) { this->defence = n; }
	void setAttack(int n) { this->attack = n; }
	void setStrength(int n) { this->strength = n; }
	void setLuck(int n) { this->luck = luck; }

private:
	int defence;
	int strength;
	int attack;
	int luck;

	int armorType;
	int lvlReq;
};

#endif
