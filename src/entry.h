#ifndef ENTRY_H
#define ENTRY_H

#include <iostream>
#include <string>

class entry{ // define the entry class
  public:
    entry(std::string, int, int, int);
    std::string playerName;
    int playerLevel;
    int playerXp;
    int playerGold;
};

#endif