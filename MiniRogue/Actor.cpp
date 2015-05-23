//
//  Actor.cpp
//  MiniRogue
//
//  Created by Chenguang Liu on 5/22/15.
//  Copyright (c) 2015 Chenguang Liu. All rights reserved.
//

#include "Actor.h"

// Constructor
Actor::Actor(string name, int hitPoints, int armorPoints, int strengthPoints, int dexterityPoints) {
    m_name = name;
    m_hit_points = hitPoints;
    m_armor_points = armorPoints;
    m_strength_points = strengthPoints;
    m_dexterity_points = dexterityPoints;
}
// Destructor
Actor::~Actor() {
    delete m_weapon;
}

// Accessors
int Actor::getRow() const {
    return m_row;
}

int Actor::getCol() const {
    return m_col;
}

string Actor::getName() const {
    return m_name;
}

int Actor::getHitPoints() const {
    return m_hit_points;
}

int Actor::getArmorPoints() const {
    return m_armor_points;
}

int Actor::getStrengthPoints() const {
    return m_strength_points;
}

int Actor::getDexterityPoints() const {
    return m_dexterity_points;
}

int Actor::getSleepTime() const {
    return m_sleep_time;
}

Weapon* Actor::getWeapon() const {
    return m_weapon;
}

// Muatators
void Actor::setRow(int row) {
    if (row < 0 || row >= 18) {
        return;
    }
    m_row = row;
}

void Actor::setCol(int col) {
    if (col < 0 || col >= 70) {
        return;
    }
    m_col = col;
}

void Actor::setHitPoints(int hitPoints) {
    if (hitPoints > 99) {
        m_hit_points = 99;
    } else {
        m_hit_points = hitPoints;
    }
}

void Actor::setArmorPoints(int armorPoints) {
    if (armorPoints < 0 || armorPoints > 99) {
        return;
    }
    m_armor_points = armorPoints;
}

void Actor::setStrengthPoints(int strengthPoints) {
    if (strengthPoints < 0 || strengthPoints > 99) {
        return;
    }
    m_strength_points = strengthPoints;
}

void Actor::setDexterityPoints(int dexterityPoints) {
    if (dexterityPoints < 0 || dexterityPoints > 99) {
        return;
    }
    m_dexterity_points = dexterityPoints;
}

void Actor::setSleepTime(int sleepTime) {
    if (sleepTime < 0 || sleepTime > 9) {
        return;
    }
    m_sleep_time = sleepTime;
}

void Actor::setWeapon(Weapon* weapon) {
    m_weapon = weapon;
}