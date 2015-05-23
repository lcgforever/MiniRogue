//
//  Actor.h
//  MiniRogue
//
//  Created by Chenguang Liu on 5/22/15.
//  Copyright (c) 2015 Chenguang Liu. All rights reserved.
//

#ifndef MiniRogue_Actor_h
#define MiniRogue_Actor_h

#include <string>
#include "Weapon.h"
using namespace std;

class Actor {
public:
    // Constructor
    Actor(string name, int hitPoints, int armorPoints, int strengthPoints, int dexterityPoints);
    // Destructor
    ~Actor();
    
    // Accessors
    int getRow() const;
    int getCol() const;
    string getName() const;
    int getHitPoints() const;
    int getArmorPoints() const;
    int getStrengthPoints() const;
    int getDexterityPoints() const;
    int getSleepTime() const;
    Weapon* getWeapon() const;
    
    // Muatators
    void setRow(int row);
    void setCol(int col);
    void setHitPoints(int hitPoints);
    void setArmorPoints(int armorPoints);
    void setStrengthPoints(int strengthPoints);
    void setDexterityPoints(int dexterityPoints);
    void setSleepTime(int sleepTime);
    void setWeapon(Weapon* weapon);
    
private:
    // The actor's current position in the level
    int m_row;
    int m_col;
    // The actor's name
    string m_name;
    // Hit points, from 0 to 99, die when <= 0
    int m_hit_points;
    // Armor points, from 0 to 99
    int m_armor_points;
    // Strength points, from 0 to 99
    int m_strength_points;
    // Dexterity points, an integer from 0 to 99
    int m_dexterity_points;
    // sleep time, an integer from 0 to 9
    // indicating how long the actor will sleep
    int m_sleep_time;
    // Actor's weapon
    Weapon* m_weapon;
};

#endif
