#pragma once
#include "Input.cpp"
#include "Events.h"
#include <iostream>

class Game
{

public:
	//Constructor
	Game();

	virtual ~Game();

	//Attributes
	bool isRunning;

	//Define game objects here and initialize with its constructor int init() function.
	Player player;
	Events eventHandler;
	//Shop shop;

	//Functions
	void init();
	int mainMenu();
	int showShopOptions();
	void displayCharacterOptions();
	void displayOptions();
	void showLogo();
	bool loginScreen();

	//Getters
	void setLoggedInStatus(bool val);
	//Setters
	bool getLoggedInStatus();
private:
	bool isLoggedIn = false;
};

//TODO:
// - ADD States

