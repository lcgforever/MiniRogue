//
//  Player.h
//  MiniRogue
//
//  Created by Chenguang Liu on 5/22/15.
//  Copyright (c) 2015 Chenguang Liu. All rights reserved.
//

#ifndef __MiniRogue__Player__
#define __MiniRogue__Player__

#include "Actor.h"
#include "Inventory.h"
#include "Scroll.h"

class Player : public Actor {
public:
    // Constructor
    Player();
    
    void pickUpItem(GameObject* item);
    void wieldWeapon(Weapon* weapon);
    void readScroll(GameObject* item);
    
private:
    Inventory inventory;
};

#endif /* defined(__MiniRogue__Player__) */
