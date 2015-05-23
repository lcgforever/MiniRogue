//
//  Scroll.h
//  MiniRogue
//
//  Created by Chenguang Liu on 5/22/15.
//  Copyright (c) 2015 Chenguang Liu. All rights reserved.
//

#ifndef MiniRogue_Scroll_h
#define MiniRogue_Scroll_h

// This is Scroll.h
/*
 Scroll class is derived from GameObjects
 */
#include "GameObject.h"
#include "utilities.h"

class Scroll : public GameObject {
public:
    // Constructor
    Scroll(string name) : GameObject(name) {}
    
    // Use scroll
    virtual int getUpgradePoints() const = 0;
    
    enum ScrollType {
        TELEPORTATION,
        IMPROVE_ARMOR,
        RAISE_STRENGTH,
        ENHANCE_HEALTH,
        ENHANCE_DEXTERITY
    };
    
    // Scroll type
    virtual ScrollType getType() const = 0;
};

class TeleScroll : public Scroll {
public:
    // constructor
    TeleScroll() : Scroll("scroll of teleportation") {}
    
    virtual int getUpgradePoints() const = 0;
    
    virtual ScrollType getType() const {
        return TELEPORTATION;
    }
};

class ArmorScroll : public Scroll {
public:
    // constructor
    ArmorScroll() : Scroll("scroll of improve armor") {}
    
    virtual int getUpgradePoints() const {
        return randInt(3) + 1;
    }
    
    virtual ScrollType getType() const {
        return IMPROVE_ARMOR;
    }
};

class StrengthScroll : public Scroll {
public:
    StrengthScroll() : Scroll("scroll of raise strength") {}
    
    virtual int getUpgradePoints() const {
        return randInt(3) + 1;
    }
    
    virtual ScrollType getType() const {
        return RAISE_STRENGTH;
    }
};

class HealthScroll : public Scroll {
public:
    HealthScroll() : Scroll("scroll of enhance health") {}
    
    virtual int getUpgradePoints() const {
        return randInt(6) + 3;
    }
    
    virtual ScrollType getType() const {
        return ENHANCE_HEALTH;
    }
};

class DexterityScroll : public Scroll {
public:
    DexterityScroll() : Scroll("enhance dexterity") {}
    
    virtual int getUpgradePoints() const {
        return 1;
    }
    
    virtual ScrollType getType() const {
        return ENHANCE_DEXTERITY;
    }
};

#endif
