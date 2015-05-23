//
//  Player.cpp
//  MiniRogue
//
//  Created by Chenguang Liu on 5/22/15.
//  Copyright (c) 2015 Chenguang Liu. All rights reserved.
//

#include "Player.h"

Player::Player() : Actor("player", 20, 2, 2, 2) {
    ShortSword* shortSword;
    setWeapon(shortSword);
    inventory.add(shortSword);
}