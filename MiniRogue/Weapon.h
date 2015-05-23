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
    Weapon(string name, int dex_bonus, int damage_amount): GameObject(name) {
        m_dex_bonus = dex_bonus;
        m_damage_amount = damage_amount;
    }
    // Accessor
    int getDexBonus() const {
        return m_dex_bonus;
    }
    int getDamageBonus() const {
        return m_damage_amount;
    }
    
    // Weapon action string
    virtual string getWeaponAction() const = 0;
    
private:
    // A dexterity bonus
    int m_dex_bonus;
    // A damage amount
    int m_damage_amount;
};

class Mace : public Weapon {
public:
    Mace() : Weapon("mace", 0, 2) {}
    
    virtual string getWeaponAction() const {
        return "swings";
    }
};

class ShortSword : public Weapon {
public:
    ShortSword() : Weapon("short sword", 0, 2) {}
    
    virtual string getWeaponAction() const {
        return "slashes";
    }
};

class LongSword : public Weapon {
public:
    LongSword() : Weapon("long sword", 2, 4) {}
    
    virtual string getWeaponAction() const {
        return "swings";
    }
};

class MagicAxe : public Weapon {
public:
    MagicAxe() : Weapon("magic axe", 5, 5) {}
    
    virtual string getWeaponAction() const {
        return "chops";
    }
};

class MagicFang : public Weapon {
public:
    MagicFang() : Weapon("magic fang of sleep", 3, 2) {}
    
    virtual string getWeaponAction() const {
        return "strikes";
    }
};

#endif //Weapon_INCLUDED
