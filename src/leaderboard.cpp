#include <iostream>
#include <string>
#include "leaderboard.h"

leaderboard::leaderboard (std::vector<entry> leaderboardEntries) {
  // This is the leaderboard constructer method. Pass a vector of type entry. 
  entries = leaderboardEntries;
}

int leaderboard::findLengthOfInt(int inputNumber){
  // pass a int to find the Length of the int. The length of the int is how many times the int can be / by 10 
  if(inputNumber < 10){ // if the int is < 10 then there is only one
    return 1;
  }
  int lengthCount = 0;
  for(; inputNumber != 0; inputNumber /= 10, lengthCount++); //divide the int by 10
  return lengthCount;
}

bool leaderboard::displayLeaderboard(){
  // display the leaderboard in the terminal. Takes no peramiters and returns a bool. The moethod will return true when no errors and false when error.
  try{
      std::cout << "Name           Level     Xp        Gold      \n";
      for(int i = 0; i < entries.size();i++){
        //write player name in table
        std::cout << entries[i].playerName;
        for(int x = entries[i].playerName.size(); x < 15; x++){ // fill with spaces 
          std::cout << " ";
        }
        //write player level in table
        std::cout << entries[i].playerLevel;
        for(int x = findLengthOfInt(entries[i].playerLevel); x < 10; x++){ // fill with spaces 
          std::cout << " ";
        }
        //write player xp in table
        std::cout << entries[i].playerXp;
        for(int x = findLengthOfInt(entries[i].playerXp); x < 10; x++){ // fill with spaces 
          std::cout << " ";
        }
        //write player gold in table
        std::cout << entries[i].playerGold;
        for(int x = findLengthOfInt(entries[i].playerGold); x < 10; x++){ // fill with spaces 
          std::cout << " ";
        }
        std::cout << std::endl;
      }
    return true;
  }
  catch(...){
    return false;
  }
}

