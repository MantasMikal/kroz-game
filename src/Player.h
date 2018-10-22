#ifndef PLAYER_H
#define PLAYER_H
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Monster.h"
#include "Inventory.h"
#include <string>

class Player
{
private:

	//Info
	//std::string login;
	//std::string password;

	//Coordinates for 2D array
	int xPos;
	int yPos;


	//STATS
	int LVL;
	int XP;
	int XPTillNext;
	int STR;
	int ATT;
	int DEF;
	int LCK;

	int GP;
	int ID;

	string name;
	string username;
	string password;
	int maxHealth;
	int currentHealth;
	int fleePossible;


public:

	Player();
	~Player();

	Inventory inv;
	array<Armor, 5> equipment;
	int reqExperience[20] = { 0, 100, 200, 400, 800, 1200, 2000, 3000, 4000, 5000, 6500, 8000 };
	Weapon mainWeapon;
	Weapon sideWeapon;

	//GETTERS
	int getXPos();
	int getYPos();
	int getLVL();
	int getXP();
	int getXPTillNext();
	int getSTR();
	int getATT();
	int getDEF();
	int getLCK();
	int getGP();
	int getID();
	int getMaxHealth();
	int getCurrentHealth();

	std::string getUsername();
	std::string getPassword();
	string getName();

	//SETTERS
	void setXPos(int n);
	void setYPos(int n);
	void setLVL(int n);
	void setXP(int n);
	void setXPTillNext(int n);
	void setSTR(int n);
	void setATT(int n);
	void setDEF(int n);
	void setLCK(int n);
	void setGP(int n);
	void setID(int n);
	void setUsername(std::string n);
	void setPassword(std::string n);
	void setName(string n);
	void setMaxHealth(int n);
	void setCurrentHealth(int n);


	//Functions
	bool levelUp();
	void init();
	void move(int dir);//Works, but needs testing
	void printStats(); //Convert to string
	void clearEquipment();
	void consumeItem(Item* item, int index = -1);
	void equipWeapon(Item* item, int index = -1);
	void equipArmor(Item* item, int index = -1);
	void unequipArmor(Armor item);//Works, but needs testing
	void unequipWeapon(Weapon item);//Works, but needs testing
	void attack(Monster &monster); //Need monster class
	void battleOptions(Monster &monster);
	void displayItems();
	void displayEquipment();
	string printHealth();
	bool isLevelUpAvailable();
	void printAllItems();



};

#endif
