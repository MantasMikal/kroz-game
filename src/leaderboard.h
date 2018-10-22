#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <iostream>
#include <string>
#include "entry.h"
#include <vector>

class leaderboard { // define the leadabord class
  public:
    leaderboard (std::vector<entry>);
    std::vector<entry> entries;
    bool displayLeaderboard();
    int findLengthOfInt(int);
};

#endif
