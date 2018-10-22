#include "Shop.h"
#include "Input.cpp"
#include <iostream>
#include <string>


Shop::Shop() {

}

void Shop::printWeapons() {
	for (int i = 0; i < 10; i++) {
		if (this->weapons[i].getName() != "NONE") {
			std::cout << i + 1 << ". " << weapons[i].getName() << "\n";
			cout << "  Level Req    >> " << weapons[i].getLvlReq() << endl;
			cout << "     Attack    >> " << weapons[i].getAttack() << endl;
			cout << "   Strength    >> " << weapons[i].getStrength() << endl;
			cout << "    Defence    >> " << weapons[i].getDefence() << endl;
			cout << "       Luck    >> " << weapons[i].getLuck() << endl;
			cout << "      Price    >> " << weapons[i].getValue() << endl;

		}
		else continue;
	}
}

void Shop::printArmor() {
	for (int i = 0; i < 10; i++) {
		if (this->equipment[i].getName() != "NONE") {
			std::cout << i + 1 << ". " << equipment[i].getName() << "\n";
			cout << "  Level Req    >> " << equipment[i].getLvlReq() << endl;
			cout << "     Attack    >> " << equipment[i].getAttack() << endl;
			cout << "   Strength    >> " << equipment[i].getStrength() << endl;
			cout << "    Defence    >> " << equipment[i].getDefence() << endl;
			cout << "       Luck    >> " << equipment[i].getLuck() << endl;
			cout << "      Price    >> " << equipment[i].getValue() << endl;

		}
		else continue;
	}
}

void Shop::printConsumables() {
	for (int i = 0; i < 10; i++) {
		if (this->consumables[i].getName() != "NONE") {
			std::cout << i + 1 << ". " << consumables[i].getName() << "\n";
			cout << "HealthBoost    >> " << consumables[i].getHealthBoost() << endl;
			cout << "DefenceBoost   >> " << consumables[i].getDefenceBoost() << endl;
			cout << "AttackBoost    >> " << consumables[i].getAttackBoost() << endl;
			cout << "      Price    >> " << consumables[i].getValue() << endl;

		}
		else continue;

	}
}

Armor Shop::getArmor(int index) {
	return this->equipment[index];
}

Weapon Shop::getWeapon(int index) {
	return this->weapons[index];
}

Consumable Shop::getConsumable(int index) {
	return this->consumables[index];
}

bool Shop::buyWeapon(Player &player, int index) {
	if (player.getGP() >= 0) {//TODO
		player.inv.addItem(this->getWeapon(index));
		player.setGP(player.getGP() - 1); //TODO: NEED TO KNOW PRICE
		std::cout << "Purchase successful\n";
		return true;
	}
	else {
		std::cout << "Not enough GOLD!";
		return false;
	}

}

bool Shop::buyArmor(Player &player, int index) {
	if (player.getGP() >= 0) {//TODO
		player.inv.addItem(this->getArmor(index));
		player.setGP(player.getGP() - 1); //TODO: NEED TO KNOW PRICE
		std::cout << "Purchase successful\n";

		return true;
	}
	else {
		std::cout << "Not enough GOLD!";
		return false;
	}
}

bool Shop::buyConsumable(Player &player, int index) {
	if (player.getGP() >= 0) {//TODO
		player.inv.addItem(this->getConsumable(index));
		player.setGP(player.getGP() - 1); //TODO: NEED TO KNOW PRICE
		std::cout << "Purchase successful\n";
		return true;
	}
	else {
		std::cout << "Not enough GOLD!";
		return false;
	}
}


int Shop::showShopOptions(Player &player) {
	this->displayLogo();
	int userInput;

	//DB::getInstance()->select("SELECT * FROM Student");
	std::cout << " =========== SHOP " << "" << " ===========\n";
	std::cout << "1. Buy\n";
	std::cout << "2. Sell\n";
    std::cout << "0. EXIT\n";
	userInput = input<int>();
	switch (userInput) {
	default:
		break;
	case 0:
		this->setIsFinished(true);
		break;
	case 1:
		this->displayLogo();
		std::cout << "1. Weapons\n2. Armor\n3. Consumables\n0. EXIT\n";
		userInput = input<int>();

		switch (userInput) {
		default:
			break;
		case 0:
			this->setIsFinished(true);

		case 1:
			std::cout << "======== LIST OF WEAPONS =========\n";
			this->printWeapons();

			std::cout << "Enter item number you want to buy (0. Exit): ";
			userInput = input<int>();

			if (userInput == 0) {
				break;
				//this->setIsFinished(true);
			}
			else this->buyWeapon(player, userInput - 1);

			break;

		case 2:

			std::cout << "====== LIST OF ARMOR =======\n";
			this->printArmor();

			std::cout << "Enter item number you want to buy (0. Exit): ";
			userInput = input<int>();

			if (userInput == 0) {
				break;
				//this->setIsFinished(true);
			}
			else this->buyArmor(player, userInput - 1);

			break;

		case 3:

			std::cout << "====== LIST OF CONSUMABLES =======\n";
			this->printConsumables();

			std::cout << "Enter item number you want to buy (0. Exit): ";
			userInput = input<int>();

			if (userInput == 0) {
				break;
				//this->setIsFinished(true);
			}
			else this->buyConsumable(player, userInput - 1);
			break;
		}

		break;

	case 2: {
		this->displayLogo();
		std::cout << "====== LIST OF ITEMS =========\n";
		player.printAllItems();
		std::cout << "Enter item number you want to sell (0 to exit): ";
		userInput = input<int>();
		if (userInput == 0) this->setIsFinished(true);
		this->sell(player, userInput - 1); //+1 to keep 0 as exit
		break;
	}

	}

	return false;
}

bool Shop::sell(Player &player, int index) {
	player.inv.removeItem(index);
	player.setGP(player.getGP() + 20);
	std::cout << "Item has been sold!\n";
	return true;
	//TODO:
	//Fix getting item price
}

void Shop::addArmor(Armor armor) {
	for (int i = 0; i < equipment.size(); i++) {
		if (this->equipment[i].getName() == "NONE") {
			this->equipment[i] = armor;
			break;
		}
		else continue;
	}
}

void Shop::addConsumable(Consumable consumable) {
	for (int i = 0; i < this->consumables.size(); i++) {
		if (this->consumables[i].getName() == "NONE") {
			this->consumables[i] = consumable;
			break;
		}
		else continue;
	}
}

void Shop::addWeapon(Weapon weapon) {
	for (int i = 0; i < this->weapons.size(); i++) {
		if (this->weapons[i].getName() == "NONE") {
			this->weapons[i] = weapon;
			break;
		}
		else continue;
	}
}

bool Shop::getIsFinished() {
	return this->isFinished;
}

void Shop::setIsFinished(bool val) {
	this->isFinished = val;
}

void Shop::displayLogo() {
	std::cout << "\x1B[2J\x1B[H";
	std::cout << R"( 
              |==|____/_____________\___
              |==/UUUU|.---.---.---.|UUU\
              |=/UUUUU||___|___|___||UUUU\
              |/UUUUUU||___|___|___||UUUUU\
              /UUUUUUU"============="UUUUUU\
             /UUUUUUUUUUUUUUUUUUUUUUUUUUUUUU\__
             |""""""""""""""""""""""""""""""|=
             |== ===  SHOP  ==   ==  == =  ==|-
             |= _______________ =  _______ =|=
             |=|:::|:::|:::|:::| =|.-----.|=|-
             |=|^^^|^^^|^^^|^^^|1O|||_|_|||=|=
             |=|---+---+---+---| =|||_|_|||=|=
             |=|   |   |   |   |= ||     ||=|-
             |=|___|___|___|___| =|| == O||=|=
             |="""""o&,@%8o""""" "||     ||=|-
             |= =.o%&hjw8@&o.== ==||_____||=|-
             """"|__________|"""""/_______\" ""
                                  """""""""
    )" << std::endl << std::endl;
	std::cout << "            A dank Shop appeared!\n";
}
