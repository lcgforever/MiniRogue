//
//  Weapon.h
//  MiniRogue
//
//  Created by Chenguang Liu on 5/22/15.
//  Copyright (c) 2015 Chenguang Liu. All rights reserved.
//

#ifndef MiniRogue_Weapon_h
#define MiniRogue_Weapon_h

// This is Weapon.h
/*
 Weapon class is derived from GameObjects
 */
#include "GameObject.h"

class Weapon : public GameObject {
public:
    // Constructor
    Weapon(string name, int dex_bonus, int damage_amount, int row, int col): GameObject(name, row, col) {
        m_dex_bonus = dex_bonus;
        m_damage_amount = damage_amount;
    }
    // Destructor
    virtual ~Weapon() {}
    
    // Accessor
    int getDexBonus() const {
        return m_dex_bonus;
    }
    int getDamageBonus() const {
        return m_damage_amount;
    }
    
    // Get object type
    virtual ObjectType getObjectType() const {
        return WEAPON;
    }
    
    // Weapon action string
    virtual string getWeaponAction() const = 0;
    
    // Weapon type
    enum WeaponType {
        MACE = 0,
        SHORT_SWORD = 1,
        LONG_SWORD = 2,
        MAGIC_AXE = 3,
        MAGIC_FANGS = 4
    };
    
    virtual WeaponType getWeaponType() const = 0;
    virtual char getSymbolOnMap() const {
        return ')';
    }
    
private:
    // A dexterity bonus
    int m_dex_bonus;
    // A damage amount
    int m_damage_amount;
};

class Mace : public Weapon {
public:
    Mace(int row, int col) : Weapon("mace", 0, 2, row, col) {}
    
    virtual string getWeaponAction() const {
        return "swings";
    }
    
    virtual WeaponType getWeaponType() const {
        return MACE;
    }
};

class ShortSword : public Weapon {
public:
    ShortSword(int row, int col) : Weapon("short sword", 0, 2, row, col) {}
    
    virtual string getWeaponAction() const {
        return "slashes";
    }
    
    virtual WeaponType getWeaponType() const {
        return SHORT_SWORD;
    }
};

class LongSword : public Weapon {
public:
    LongSword(int row, int col) : Weapon("long sword", 2, 4, row, col) {}
    
    virtual string getWeaponAction() const {
        return "swings";
    }
    
    virtual WeaponType getWeaponType() const {
        return LONG_SWORD;
    }
};

class MagicAxe : public Weapon {
public:
    MagicAxe(int row, int col) : Weapon("magic axe", 5, 5, row, col) {}
    
    virtual string getWeaponAction() const {
        return "chops";
    }
    
    virtual WeaponType getWeaponType() const {
        return MAGIC_AXE;
    }
};

class MagicFang : public Weapon {
public:
    MagicFang(int row, int col) : Weapon("magic fangs", 3, 2, row, col) {}
    
    virtual string getWeaponAction() const {
        return "strikes";
    }
    
    virtual WeaponType getWeaponType() const {
        return MAGIC_FANGS;
    }
    
    int randomSleepTime() const {
        return trueWithProbability(0.2) ? randInt(5) + 2 : 0;
    }
};

#endif //Weapon_INCLUDED
