#include "Weapon.h"


Weapon::Weapon(int attack, int strength, int defence, int luck, int weaponType, int lvlReq,
	string name, string rarity, int value, int id)
	: Item(name, rarity, value, id)
{
	this->attack = attack;
	this->strength = strength;
	this->defence = defence;
	this->luck = luck;
	this->weaponType = weaponType;
	this->lvlReq = lvlReq;
}

Weapon::~Weapon()
{
}

Weapon* Weapon::clone()const
{
	return new Weapon(*this); //returns new copy of ->this for casting
}

ItemType Weapon::itemType()const
{
	return ItemType::Weapon;
}
