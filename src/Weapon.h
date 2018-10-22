#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"
class Weapon :
	public Item
{

public:
	//made shield a weapon because could have another off hand weapon such as dual swords etc. which could be cool :)
	Weapon(int attack = 0, int strength = 0, int defence = 0, int luck = 0, int weaponType = -1, int lvlReq = 1,
		string name = "NONE", string rarity = "NONE", int value = 0, int id = 0);
	~Weapon();

	//Pure virtual functions

	virtual Weapon* clone()const;
	virtual ItemType itemType()const;

	//virtual functions

	virtual int getAttack() { return this->attack; }
	virtual int getStrength() { return this->strength; }
	virtual int getDefence() { return this->defence; }
	virtual int getLuck() { return this->luck; }

	virtual int getWeaponType() { return this->weaponType; }
	virtual int getLvlReq() { return this->lvlReq; }

	//mutators

	void setAttack(int n) { this->attack = n; }
	void setStrength(int n) { this->strength = n; }
	void setDefence(int n) { this->defence = n; }
	void setLuck(int n) { this->luck = n; }

private:
	int attack;
	int strength;
	int defence; //main weapons probably wont have defence but shields might do, 
	int luck;

	int weaponType;
	int lvlReq;
};

#endif

