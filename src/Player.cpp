#include "Player.h"
#include "Input.cpp"

#include <iostream>
#include <string>
#include <typeinfo>

Player::Player()
{
	this->xPos = 0;
	this->yPos = 0;

	this->ATT = 10;
	this->DEF = 10;
	this->STR = 10;
	this->LCK = 0;

	this->LVL = 1;
	this->XP = 0;

	this->GP = 1000;

	this->name = "Player";
	this->maxHealth = 30;
	this->currentHealth = maxHealth;

	/* initialize random seed: */
	srand(time(NULL));

	/* generate secret number between 1 and 10: */
	this->ID = rand() % 10000 + 1;

	//this->inv = Inventory();
	// TODO:
	// XPTillNext
}

bool Player::levelUp() {
	//TODO 
	//Show "Level up available


	if (this->getXP() >= this->reqExperience[this->getLVL()]) {
		this->LVL++;
		std::cout << "You're getting STRONGER!\nLevel up to: " << this->LVL;
	}
	else {
		std::cout << "Not enough XP! Go to fight weakling! \n";
		std::cout << "Current XP: " << this->getXP() << "XP Till next level up: " << this->reqExperience[this->getLVL()] << "\n";
		return false;
	}
	return true;
}

bool Player::isLevelUpAvailable() {
	if (this->getXP() >= this->reqExperience[this->getLVL()]) return true;
	else return false;
}

void Player::clearEquipment() {
	for (size_t i = 0; i < equipment.size(); ++i) {
		equipment[i] = Armor();
	}
}

void Player::consumeItem(Item* item, int index) {

	if (item->getHealthBoost() > 0) {
		if (this->currentHealth + item->getHealthBoost() > this->currentHealth)
		{
			this->currentHealth = this->maxHealth;
		}
		else {
			this->currentHealth += item->getHealthBoost();
		}
	}
	else if (item->getDefenceBoost() > 0) {
		//increase defence for set number of turns? 
	}
	else if (item->getAttackBoost() > 0) {
		//increase player damage for a set number of turns?
	}

	std::cout << "Consumed " << item->getName() << endl;
	if (index != -1) {
		this->inv.removeItem(index);
	}
}

void Player::equipWeapon(Item* item, int index) {
	int weaponType = item->getWeaponType();
	switch (weaponType) {
	default:
		break;
	case 1:
	{
        if (index != -1) {
			this->inv.removeItem(index);
		}
		if (this->mainWeapon.getWeaponType() != -1) {
			unequipWeapon(this->mainWeapon);
		}



		Weapon& weapon = dynamic_cast<Weapon&>(*item);
		this->mainWeapon = weapon;

		this->ATT += weapon.getAttack();
		this->STR += weapon.getStrength();
		this->DEF += weapon.getDefence();
		this->LCK += weapon.getLuck();

		break;
	}
	case 2:
	{
        
		if (index != -1) {
			this->inv.removeItem(index);
		}

		if (this->sideWeapon.getWeaponType() != -1) {
			unequipWeapon(this->sideWeapon);
		}
		Weapon& weapon = dynamic_cast<Weapon&>(*item);
		this->sideWeapon = weapon;

		this->ATT += weapon.getAttack();
		this->STR += weapon.getStrength();
		this->DEF += weapon.getDefence();
		this->LCK += weapon.getLuck();

		break;
	}
	}
}

void Player::equipArmor(Item* item, int index) {
	Armor& armor = dynamic_cast<Armor&>(*item);
	int armorType = armor.getArmorType();
	
    if (index != -1) {
		this->inv.removeItem(index);
	}
    
    if (equipment[armorType].getArmorType() != -1) {
		unequipArmor(equipment[armorType]);
	}



	this->equipment[armorType] = armor;

	this->ATT += armor.getAttack();
	this->STR += armor.getStrength();
	this->DEF += armor.getDefence();
	this->LCK += armor.getLuck();

}

void Player::unequipArmor(Armor item) {
	int armorType = item.getArmorType();

	this->inv.addItem(item);
	this->equipment[armorType] = Armor();

	this->ATT -= item.getAttack();
	this->STR -= item.getStrength();
	this->DEF -= item.getDefence();
	this->LCK -= item.getLuck();
}

void Player::unequipWeapon(Weapon item) {
	int weaponType = item.getWeaponType();
	this->inv.addItem(item);
	switch (weaponType) {
	default:
		break;
	case 0:
		this->mainWeapon = Weapon();
		break;
	case 1:
		this->sideWeapon = Weapon();
		break;
	}
}

Player::~Player()
{
}

void Player::init() {
	// TODO:
	// Few starter items to chose from
	// We can use this for saving/loading? 


}

void Player::printStats() {
	std::cout << "= PLAYER STATS =\n";
	std::cout << "LVL: " << this->getLVL() << "\n";
	std::cout << "ATT: " << this->getATT() << "\n";
	std::cout << "DEFF: " << this->getDEF() << "\n";
	std::cout << "STR: " << this->getSTR() << "\n";
	std::cout << "LUCK: " << this->getLCK() << "\n";
	std::cout << "XP: " << this->getXP() << "\n";
	std::cout << "Gold: " << this->getGP() << "\n";
}

void Player::printAllItems() {
	if (this->inv.getItemCount() == 0) {
		cout << "Inventory is empty!" << endl;
	}
	else {
		for (int i = 0; i < this->inv.getItemCount(); i++) {
			std::cout << "[" << i + 1 << "] ";
			this->inv.printStats(this->inv.getItem(i));
		}
	}
}

void Player::displayEquipment() {
	std::cout << "-------EQUIPMENT-------" << std::endl;

	for (size_t i = 0; i < this->equipment.size(); ++i) {
		std::cout << "[" << this->equipment[i].getArmorType() << "] ";
		if (this->equipment[i].getName() == "NONE") {
			std::cout << "-EMPTY-" << std::endl;
		}
		else {
			std::cout << this->equipment[i].getName() << std::endl;
		}
	}

	std::cout << "-------WEAPONS-------" << std::endl;

	if (this->mainWeapon.getWeaponType() != -1) {
		std::cout << "[Main Weapon]" << this->mainWeapon.getName() << std::endl;
	}
	else {
		std::cout << "[Main Weapon] -EMPTY-" << std::endl;
	}

	if (this->sideWeapon.getWeaponType() != -1) {
		std::cout << "[Side Weapon]" << this->sideWeapon.getName() << std::endl;
	}
	else {
		std::cout << "[Side Weapon] -EMPTY-" << std::endl;
	}
}


void Player::displayItems() {
	if (this->inv.getItemCount() == 0) {
		cout << "Inventory is empty!" << endl;
	}
	else {
		for (int i = 0; i < this->inv.getItemCount(); ++i) {
			std::cout << "[" << i + 1 << "] ";
			this->inv.printStats(this->inv.getItem(i));
		}
		//TODO
		//Validationas;ldaskdakd
		int userInput;

		std::cout << endl << endl << "Would you like to equip / use an item? (1/0)" << endl;
		userInput = input<int>();

		if (userInput == 1) {
			//TODO
			//check if input is within range
			std::cout << "Which item would you like to equip / use? (number)" << endl;

			userInput = input<int>();

			Item* item = this->inv.getItem(userInput - 1);
			if (item->getLvlReq() <= this->getLVL()) {
				if (typeid(*item) == typeid(Consumable)) {
					this->consumeItem(item, userInput - 1);
				}
				else if (typeid(*item) == typeid(Weapon)) {
					this->equipWeapon(item, userInput - 1);
				}
				else if (typeid(*item) == typeid(Armor)) {
					this->equipArmor(item, userInput - 1);
				}
			}
			else {
				std::cout << "Cannot equip " << item->getName() << "\n You are not a high enough level!\n";
			}
		}
	}
}



string Player::printHealth() {
	if (currentHealth <= 0) {
		return name + " is dead!";
	}
	return this->name + " Health: " + to_string(this->currentHealth) + "/" + to_string(this->maxHealth);
}

void Player::battleOptions(Monster &monster) {
	// these are the options the player can choose while in battle
	// add option to attack, use consumables, and flee

    if(monster.currentHealth<=0 or this->currentHealth<=0){ // makes sure battle doesn't 
        return;                                           // start if someone is dead.
    }
    
	int choice;

	std::cout << "\n= BATTLE MENU =\n\n";
	std::cout << "1. Attack \n";
	std::cout << "2. Inventory \n";
	std::cout << "3. Flee \n";


	choice = input<int>();
    system("clear");

	switch (choice) {
	case 1:
		// variable 'enemy' will be set to whoever player is fighting
		this->attack(monster);
		battleOptions(monster);
		break;
	case 2:
		// print items and allow player to use
		this->displayItems();
		battleOptions(monster);
		break;
	case 3:
		// chance to end battle.
		int fleePossible;
		srand(time(NULL)); // initialise random seed
		fleePossible = rand() % 2; //can equate to 0 or 1
		if (fleePossible == true) {
			cout << "You have managed to escape!" << endl;
			break;
		}
		else {
			cout << monster.name << " doesn't let you escape!" << endl;
            this->setCurrentHealth(this->currentHealth - monster.ATT);
            cout << "You have taken " << monster.ATT << " damage!\n" << endl;
            cout << printHealth() << endl;
			battleOptions(monster);
		}
		break;
	default:
		std::cout << "Choose 1, 2 or 3." << endl;
		battleOptions(monster);
	}

}

void Player::attack(Monster &monster) {
	int damageDealt;

	damageDealt = this->ATT * (1+ (getSTR()/100)); // increase damage based on strength
	monster.currentHealth -= damageDealt;
	std::cout << "\n" << name << " attacked " << monster.name << " for " << damageDealt << " damage!\n";


	monster.damageDealt = monster.ATT * (1 - (getDEF()/100)) + 1; 
    // always do at least 1 damage but reduce damage depending on defence                                                                        
	currentHealth -= monster.damageDealt;
	cout << monster.name << " attacked back for " << monster.damageDealt << " damage! \n\n";


	cout << printHealth() << "\n";
	cout << monster.printHealth() << "\n\n";
}

//Getters

int Player::getATT() {
	return this->ATT;
}

int Player::getDEF() {
	return this->DEF;
}

int Player::getSTR() {
	return this->STR;
}

int Player::getLCK() {
	return this->LCK;
}

int Player::getLVL() {
	return this->LVL;
}

int Player::getXP() {
	return this->XP;
}

int Player::getXPos() {
	return this->xPos;
}

int Player::getXPTillNext() {
	return this->XPTillNext;
}

int Player::getGP() {
	return this->GP;
}

string Player::getName() {
	return this->name;
}
int Player::getMaxHealth() {
	return this->maxHealth;
}
int Player::getCurrentHealth() {
	return this->currentHealth;
}


int Player::getYPos() {
	return this->yPos;
}

int Player::getID() {
	return this->ID;
}

std::string Player::getUsername() {
	return this->username;
}

std::string Player::getPassword() {
	return this->password;
}

void Player::setATT(int n) {
	this->ATT = n;
}

void Player::setDEF(int n) {
	this->DEF = n;
}

void Player::setSTR(int n) {
	this->STR = n;
}

void Player::setLCK(int n) {
	this->LCK = n;
}

void Player::setLVL(int n) {
	this->LVL = n;
}

void Player::setXP(int n) {
	this->XP = n;
}

void Player::setXPos(int n) {
	this->xPos = n;
}

void Player::setXPTillNext(int n) {
	this->XPTillNext = n;
}

void Player::setGP(int n) {
	this->GP = n;
}


void Player::setName(string n) {
	this->name = n;
}
void Player::setMaxHealth(int n) {
	this->maxHealth = n;
}
void Player::setCurrentHealth(int n) {
	this->currentHealth = n;
}

void Player::setUsername(std::string n) {
	this->username = n;
}

void Player::setPassword(std::string n) {
	this->password = n;
}

void Player::setYPos(int n) {
	this->yPos = n;
}

void Player::setID(int n) {
	this->ID = n;
}


