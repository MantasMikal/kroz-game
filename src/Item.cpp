#include "Item.h"


Item::Item(string name, string rarity, int value, int id)
{
	this->name = name;
	this->value = value;
	this->rarity = rarity;
	this->ID = id;
}


Item::~Item()
{
}
