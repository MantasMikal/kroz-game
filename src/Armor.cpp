#include "Armor.h"


Armor::Armor(int armorType, int lvlReq, int defence, int attack, int strength, int luck,
	string name, string rarity, int value, int id)
	: Item(name, rarity, value, id)
{
	this->armorType = armorType;
	this->lvlReq = lvlReq;

	this->defence = defence;
	this->attack = attack;
	this->strength = strength;
	this->luck = luck;
}

Armor::~Armor()
{
}

Armor* Armor::clone()const
{
	return new Armor(*this); //returns new copy of ->this<-

}

ItemType Armor::itemType()const {
	return ItemType::Armor;
}