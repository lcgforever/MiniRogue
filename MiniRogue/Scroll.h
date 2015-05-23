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

class TeleScroll : public GameObject {
public:
    // constructor
    TeleScroll() : GameObject("scroll of teleportation") {};
}

class ArmorScroll : public GameObject {
public:
    // constructor
    ArmorScroll() : GameObject("scroll of improve armor") {};
    
    int getArmor() {
        return randInt(3) + 1;
    }
}

class StrengthScroll : public GameObject {
public:
    StrengthScroll() : GameObject("scroll of raise strength") {};
    
    int getStrength() {
        return randInt(3) + 1;
    }
}

class HealthScroll : public GameObject {
public:
    HealthScroll() : GameObject("scroll of enhance health") {};
    
    int getHealth() {
        return randInt(6) + 3;
    }
}

class DexterityScroll : public GameObject {
public:
    DexterityScroll() : GameObject("enhance dexterity") {};
    
    int getDexterity() {
        return 1;
    }
}

#endif
