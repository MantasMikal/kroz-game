#include "entry.h"
#include <string>

using namespace std;

entry::entry(string name, int level, int xp, int gold){
  // this is the constructer for the entry class. pass name level xp ad gold to init the entry in the leadderboard
  playerName = name;
  playerLevel = level;
  playerXp = xp;
  playerGold = gold;
}
