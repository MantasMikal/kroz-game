#include "Inventory.h"

//----Inventory Commands----
//Inventory inv; --- create a new inventory (will initialize automatically) --- fills inventory with empty pointers
//inv.addItem(CREATEITEMHERE)
//inv.removeItem(INDEXOFITEMTOREMOVE)
//inv.getItem(INDEXOFITEMTOGET) 
//
//

Inventory::Inventory()
{
	this->capacity = 10; //max of 10 items to start
	this->itemCount = 0; // current amount of items
	this->itemArr = new Item*[capacity]; //pointers of pointers
	this->initialize();
}

Inventory::~Inventory()
{
	for (int i = 0; i < this->itemCount; i++) {
		delete this->itemArr[i];
	}

	delete[] itemArr; //delete inventory when object is destroyed 

}

void Inventory::clearInventory()
{
	for (int i = 0; i < this->itemCount; ++i) {
		this->removeItem(i);
	}
}

void Inventory::initialize(const int from) { //to clear inventory, call Inventory::initialize(0)
	for (int i = from; i < capacity; i++) {
		this->itemArr[i] = nullptr; //create empty array of null pointers
	}
}

bool Inventory::checkFull() {
	if (this->itemCount >= this->capacity) {
		return true;
	}
	else {
		return false;
	}
}

void Inventory::addItem(const Item& item) {
	if (this->checkFull()) {
		cout << "Inventory is full! Could not pickup " << item.getName() << endl;
	}
	else {
		this->itemArr[itemCount++] = item.clone();
	}
}

void Inventory::removeItem(const int index) {
	//this->itemArr[index] objec still exist in memory?
	this->itemArr[index] = nullptr;
	this->shuffleItems(index); //move items down one; delete this->itemArr[index] produces seg fault >.>
	this->itemCount--;
}

void Inventory::shuffleItems(const int from) {
	for (int i = from; i < this->capacity; ++i) {
		this->itemArr[i] = this->itemArr[i + 1];
	}
}

Item* Inventory::getItem(int index) {
	Item* item = this->itemArr[index];
	return item;
}


void Inventory::printStats(Item* item) //prints an items stat based on its enum itemType; --- TODO Move
{
	//DB::getInstance()->select("SELECT * FROM Student");
	ItemType itemType = item->itemType();
	cout << "ITEM_NAME " << item->getName() << endl;
	switch (itemType) {
	default:
		cout << "NONE" << endl;
		break;
	case ItemType::Weapon:
		cout << "  Level Req    >> " << item->getLvlReq() << endl;
		cout << "     Attack    >> " << item->getAttack() << endl;
		cout << "   Strength    >> " << item->getStrength() << endl;
		cout << "    Defence    >> " << item->getDefence() << endl;
		cout << "       Luck    >> " << item->getLuck() << endl;
		cout << "      Price    >> " << item->getValue() << endl;
		break;
	case ItemType::Armor:
		cout << "  Level Req    >> " << item->getLvlReq() << endl;
		cout << "     Attack    >> " << item->getAttack() << endl;
		cout << "   Strength    >> " << item->getStrength() << endl;
		cout << "    Defence    >> " << item->getDefence() << endl;
		cout << "       Luck    >> " << item->getLuck() << endl;
		cout << "      Price    >> " << item->getValue() << endl;
		break;
	case ItemType::Consumable:
		cout << "HealthBoost    >> " << item->getHealthBoost() << endl;
		cout << "DefenceBoost   >> " << item->getDefenceBoost() << endl;
		cout << "AttackBoost    >> " << item->getAttackBoost() << endl;
		cout << "      Price    >> " << item->getValue() << endl;
		break;

	}
}






