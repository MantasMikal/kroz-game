#ifndef INVENTORY_H
#define INVENTORY_H

#include "Weapon.h"
#include "Armor.h"
#include "Consumable.h"

//use item->itemType() to check the type of item
//ItemType is defined as a enum in Item.h

class Inventory
{
public:
	Inventory();
	~Inventory();

	void addItem(const Item &item);
	void removeItem(const int index);
	void shuffleItems(const int index);
	void printStats(Item* item);
	void clearInventory();

	bool checkFull();

	Item* getItem(int index);

	//accessors

	const int& getCapacity() const { return this->capacity; }
	const int& getItemCount() const { return this->itemCount; }
private:
	int capacity;
	int itemCount;
	Item** itemArr; //pointer of pointers (points to a set of pointers)

	void initialize(const int from = 0);
};

#endif

