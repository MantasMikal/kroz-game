#include "Consumable.h"


Consumable::Consumable(int healthBoost, int attackBoost, int defenceBoost,
	string name, string rarity, int value, int id) :
	Item(name, rarity, value, id)
{
	this->healthBoost = healthBoost;
	this->attackBoost = attackBoost;
	this->defenceBoost = defenceBoost;
}

Consumable::~Consumable()
{
}

Consumable* Consumable::clone()const {
	return new Consumable(*this);
}

ItemType Consumable::itemType()const {
	return ItemType::Consumable;
}
