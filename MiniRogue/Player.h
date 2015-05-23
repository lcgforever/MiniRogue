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
    // Destructor
    ~Player();
    
    // Actions
    void pickUpItem(GameObject* item);
    bool wieldWeapon(char pos);
    bool readScroll(char pos);
    
private:
    Inventory* m_inventory;
};

#endif /* defined(__MiniRogue__Player__) */
