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

class Scroll : public GameObject {
public:
    // Constructor
    Scroll(string name, int row, int col) : GameObject(name, row, col) {}
    // Destructor
    virtual ~Scroll() {}
    
    // Use scroll
    virtual int getUpgradePoints() const = 0;
    
    // Get object type
    virtual ObjectType getObjectType() const {
        return SCROLL;
    }
    
    enum ScrollType {
        IMPROVE_ARMOR = 0,
        RAISE_STRENGTH = 1,
        ENHANCE_HEALTH = 2,
        ENHANCE_DEXTERITY = 3,
        TELEPORTATION = 4
    };
    
    // Scroll type
    virtual ScrollType getScrollType() const = 0;
    virtual char getSymbolOnMap() const {
        return '?';
    }
};

class TeleScroll : public Scroll {
public:
    // constructor
    TeleScroll(int row, int col) : Scroll("scroll of teleportation", row, col) {}
    
    virtual int getUpgradePoints() const {
        return -1;
    }
    
    virtual ScrollType getScrollType() const {
        return TELEPORTATION;
    }
};

class ArmorScroll : public Scroll {
public:
    // constructor
    ArmorScroll(int row, int col) : Scroll("scroll of improve armor", row, col) {}
    
    virtual int getUpgradePoints() const {
        return randInt(3) + 1;
    }
    
    virtual ScrollType getScrollType() const {
        return IMPROVE_ARMOR;
    }
};

class StrengthScroll : public Scroll {
public:
    StrengthScroll(int row, int col) : Scroll("scroll of raise strength", row, col) {}
    
    virtual int getUpgradePoints() const {
        return randInt(3) + 1;
    }
    
    virtual ScrollType getScrollType() const {
        return RAISE_STRENGTH;
    }
};

class HealthScroll : public Scroll {
public:
    HealthScroll(int row, int col) : Scroll("scroll of enhance health", row, col) {}
    
    virtual int getUpgradePoints() const {
        return randInt(6) + 3;
    }
    
    virtual ScrollType getScrollType() const {
        return ENHANCE_HEALTH;
    }
};

class DexterityScroll : public Scroll {
public:
    DexterityScroll(int row, int col) : Scroll("enhance dexterity", row, col) {}
    
    virtual int getUpgradePoints() const {
        return 1;
    }
    
    virtual ScrollType getScrollType() const {
        return ENHANCE_DEXTERITY;
    }
};

#endif
