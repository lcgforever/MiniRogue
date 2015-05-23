//
//  Dungeon.h
//  MiniRogue
//
//  Created by Chenguang Liu on 5/22/15.
//  Copyright (c) 2015 Chenguang Liu. All rights reserved.
//

#ifndef __MiniRogue__Dungeon__
#define __MiniRogue__Dungeon__

#include <iostream>
#include <unordered_map>
using namespace std;

class Dungeon {
public:
    Dungeon();
    void generate();
    void display() const;
    int getCurrentLevel() const;
    void incrementLevel();
    
private:
    char map[18][70];
    unordered_map<int, bool> ocupiedPositions;
    int currentLevel;
};

#endif /* defined(__MiniRogue__Dungeon__) */
