//
//  Dungeon.cpp
//  MiniRogue
//
//  Created by Chenguang Liu on 5/22/15.
//  Copyright (c) 2015 Chenguang Liu. All rights reserved.
//

#include "utilities.h"
#include "Dungeon.h"

Dungeon::Dungeon() {
    currentLevel = 0;
}

void Dungeon::generate() {
    ocupiedPositions.clear();
    int r, c, objectCount;;
    
    // Generate walls and rooms
    for (r = 0; r < 18; r++) {
        for (c = 0; c < 70; c++) {
            if (r >= 5 && r <= 12 && c >= 10 && c < 60) {
                map[r][c] = ' ';
            } else {
                map[r][c] = '#';
            }
        }
    }
    
    // Generate 2 or 3 objects (Weapons or scrolls) and the stairway
    objectCount = trueWithProbability(0.5) ? 2 : 3;
    for (int i = 0; i < objectCount + 1; i++) {
        do {
            r = 5 + randInt(8);
            c = 10 + randInt(50);
        } while (ocupiedPositions[r + c]);
        ocupiedPositions[r + c] = true;
        map[r][c] = (i == 0 ? '>' : 'O');
    }
    ocupiedPositions.clear();
    
    // Generate 2 + randInt(5*(L+1)) monsters and the player
    objectCount = 2 + randInt(5 * (currentLevel + 1));
    for (int i = 0; i < objectCount + 1; i++) {
        do {
            r = 5 + randInt(8);
            c = 10 + randInt(50);
        } while (ocupiedPositions[r + c]);
        ocupiedPositions[r + c] = true;
        map[r][c] = (i == 0 ? '@' : 'M');
    }
}

void Dungeon::display() const {
    for (int r = 0; r < 18; r++) {
        for (int c = 0; c < 70; c++) {
            cout << map[r][c];
        }
        cout << endl;
    }
}

int Dungeon::getCurrentLevel() const {
    return currentLevel;
}

void Dungeon::incrementLevel() {
    currentLevel++;
}
