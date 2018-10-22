#ifndef MONSTER_H
#define MONSTER_H

#include "Consumable.h"
#include "Weapon.h"
#include "Armor.h"

#include <string>

class Monster {
public:

	//constructor
	Monster(int level);

	//variables

	string name;
	int maxHealth;
	int currentHealth;
	int ATT;
	int LVL;
	int damageDealt;

	int xp; // this xp will be given to the player

	//Getters

	string getName();
	int getMaxHealth();
	int getCurrentHealth();
	int getLVL();
	int getATT();
	int getXP();


	//Setters

	void setName(string n);
	void setMaxHealth(int n);
	void setCurrentHealth(int n);
	void setLVL(int n);
	void setATT(int n);
	void setXP(int n);

	//Functions
	void setValues(); // adds to base stats according to level
	string printHealth();

};

#endif
