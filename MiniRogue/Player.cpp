//
//  Player.cpp
//  MiniRogue
//
//  Created by Chenguang Liu on 5/22/15.
//  Copyright (c) 2015 Chenguang Liu. All rights reserved.
//

#include "Player.h"

// Constructor
Player::Player() : Actor("player", 20, 2, 2, 2) {
    ShortSword* shortSword;
    setWeapon(shortSword);
    m_inventory->add(shortSword);
}

// Destructor
Player::~Player() {
    delete m_inventory;
}

// Actions
void Player::pickUpItem(GameObject* item) {
    if (m_inventory->getItemCount() == 26) {
        cout << "Your knapsack is full; you can't pick that up." << endl;
        return;
    } else {
        m_inventory->add(item);
        cout << "You picked up a " << item->getName() << endl;
    }
}

bool Player::wieldWeapon(char pos) {
    string name = m_inventory->getItem(pos)->getName();
    Weapon* newWeapon = dynamic_cast<Weapon*>(m_inventory->getItem(pos));
    if (newWeapon == nullptr) {
        cout << "You can't wield " << name << endl;
        return false;
    }
    Weapon* currentWeapon = getWeapon();
    if (currentWeapon->getName() == newWeapon->getName()) {
        cout << "You are wielding " << name << endl;
        return true;
    }
    setWeapon(newWeapon);
    m_inventory->remove(pos);
    m_inventory->add(currentWeapon);
    cout << "You are wielding " << name << endl;
    return true;
}

bool Player::readScroll(char pos) {
    Scroll* scroll = dynamic_cast<Scroll*>(m_inventory->getItem(pos));
    if (scroll == nullptr) {
        return false;
    }
    m_inventory->remove(pos);
    switch (scroll->getType()) {
        case Scroll::TELEPORTATION:
            // Should teleport the player to a random position which is not a wall or monster
            
            cout << "You feel your body wrenched in space and time." << endl;
            break;
            
        case Scroll::IMPROVE_ARMOR:
            setArmorPoints(getArmorPoints() + scroll->getUpgradePoints());
            cout << "Your armor glows blue." << endl;
            break;
            
        case Scroll::RAISE_STRENGTH:
            setStrengthPoints(getArmorPoints() + scroll->getUpgradePoints());
            cout << "Your muscles bulge." << endl;
            break;
            
        case Scroll::ENHANCE_HEALTH:
            setHitPoints(getHitPoints() + scroll->getUpgradePoints());
            cout << "You feel your heart beating stronger." << endl;
            break;
            
        case Scroll::ENHANCE_DEXTERITY:
            setDexterityPoints(getDexterityPoints() + scroll->getUpgradePoints());
            cout << "You feel like less of a klutz." << endl;
            break;
            
        default:
            break;
    }
    return true;
}