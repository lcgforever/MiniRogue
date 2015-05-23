//
//  Inventory.h
//  MiniRogue
//
//  Created by Chenguang Liu on 5/22/15.
//  Copyright (c) 2015 Chenguang Liu. All rights reserved.
//

#ifndef __MiniRogue__Inventory__
#define __MiniRogue__Inventory__

// Inventory.h

/*
 public member function:
 (1) display: display the inventory at command w, r, i:
 Inventory:
 a. short sword
 b. long sword
 c. a scroll of strength
 d. long sword
 (2) add an item(either a weapon or scroll) to player's inventory
 If the player's inventory is not full, the item
 will be removed from the level's floor and added to the player's inventory.
 
 (3) remove
 when a scroll is read at command r, the scroll shoul be erased form the inventory
 
 private member data:
 (1) a vector of string to store weapons and scrolls
 (2) int m_capacity, the max capacity of inventory is 26
 */


#include <iostream>
#include <vector>
#include "GameObject.h"
using namespace std;

class Inventory {
public:
    // Constructor
    Inventory();
    // Destructor
    ~Inventory();
    
    // Accessor
    void display() const;
    size_t getItemCount() const;
    
    // Mutator
    void remove(char num);
    void add(GameObject* item);
    
private:
    vector<GameObject*> items;
};

#endif /* defined(__MiniRogue__Inventory__) */
