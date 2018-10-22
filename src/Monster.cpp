#include "Monster.h"
#include "Game.h"

#include <string>
#include <stdlib.h> // for rand() function
#include <time.h> // also needed for rand()

// rand() % a + b;  where b = minimum   &   a+b - 1 = maximum


//constructor

Monster::Monster(int level) {
	this->LVL = level; // this is used to increase their base stats depending on level   
}

void Monster::setValues() {
	this->maxHealth += this->LVL;
    this->currentHealth = this->maxHealth;
	this->ATT += this->LVL;
}

string Monster::printHealth() {
	if (currentHealth <= 0) {
		return name + " is dead!";
	}
	return this->name + " Health: " + to_string(this->currentHealth) + "/" + to_string(this->maxHealth);
}


// getters

string Monster::getName() { return this->name; }
int Monster::getMaxHealth() { return this->maxHealth; }
int Monster::getCurrentHealth() { return this->currentHealth; }
int Monster::getATT() { return this->ATT; }
int Monster::getLVL() { return this->LVL; }
int Monster::getXP() { return this->xp; }

// setters

void Monster::setName(string n) { this->name = n; }
void Monster::setMaxHealth(int n) { this->maxHealth = n; }
void Monster::setCurrentHealth(int n) { this->currentHealth = n; }
void Monster::setATT(int n) { this->ATT = n; }
void Monster::setLVL(int n) { this->LVL = n; }
void Monster::setXP(int n) { this->xp = n; }