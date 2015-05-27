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
    Player(int row, int col);
    // Copy constructor
    Player(const Player& other);
    // Assignment operator
    Player& operator=(const Player& other);
    // Destructor
    ~Player() {}
    
    bool canPickUpItem() const;
    bool canGetItemByPos(char pos) const;
    bool pickedUpGoldenIdol() const;
    
    // Mutators
    void setMaxHitPoints(int points);
    void setPickedUpGoldenIdol();
    
    // Actions
    void pickUpItem(char objectType, GameObject* item);
    string wieldWeapon(char pos);
    string readScroll(char pos);
    virtual void regainHitPoints();
    void openInventory();
    
private:
    Inventory m_inventory;
    int m_max_hit_points;
    bool getGoldenIdol;
};

#endif /* defined(__MiniRogue__Player__) */
