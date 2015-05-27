//
//  Actor.cpp
//  MiniRogue
//
//  Created by Chenguang Liu on 5/22/15.
//  Copyright (c) 2015 Chenguang Liu. All rights reserved.
//

#include "Actor.h"

// Constructor
Actor::Actor(string name, int hitPoints, int armorPoints, int strengthPoints, int dexterityPoints, int row, int col) {
    m_name = name;
    m_hit_points = hitPoints;
    m_armor_points = armorPoints;
    m_strength_points = strengthPoints;
    m_dexterity_points = dexterityPoints;
    m_row = row;
    m_col = col;
    m_dead_status = false;
    m_sleep_time = 0;
    m_weapon = new ShortSword(row, col);
}

// Copy constructor
Actor::Actor(const Actor& other) {
    cout << "Actor copy called" << endl;
    m_row = other.getRow();
    m_col = other.getCol();
    m_name = other.getName();
    m_hit_points = other.getHitPoints();
    m_armor_points = other.getArmorPoints();
    m_strength_points = other.getStrengthPoints();
    m_dexterity_points = other.getDexterityPoints();
    m_sleep_time = other.getSleepTime();
    m_dead_status = other.isDead();
    switch (other.getWeapon()->getWeaponType()) {
        case Weapon::MACE:
            m_weapon = new Mace(m_row, m_col);
            break;
            
        case Weapon::SHORT_SWORD:
            m_weapon = new ShortSword(m_row, m_col);
            break;
            
        case Weapon::LONG_SWORD:
            m_weapon = new LongSword(m_row, m_col);
            break;
            
        case Weapon::MAGIC_AXE:
            m_weapon = new MagicAxe(m_row, m_col);
            break;
            
        case Weapon::MAGIC_FANGS:
            m_weapon = new MagicFang(m_row, m_col);
            break;
            
        default:
            break;
    }
}

// Assignment operator
Actor& Actor::operator=(const Actor& other) {
    cout << "Actor assignment called" << endl;
    if (this != &other) {
        delete m_weapon;
        
        m_row = other.getRow();
        m_col = other.getCol();
        m_name = other.getName();
        m_hit_points = other.getHitPoints();
        m_armor_points = other.getArmorPoints();
        m_strength_points = other.getStrengthPoints();
        m_dexterity_points = other.getDexterityPoints();
        m_sleep_time = other.getSleepTime();
        m_dead_status = other.isDead();
        switch (other.getWeapon()->getWeaponType()) {
            case Weapon::MACE:
                m_weapon = new Mace(m_row, m_col);
                break;
                
            case Weapon::SHORT_SWORD:
                m_weapon = new ShortSword(m_row, m_col);
                break;
                
            case Weapon::LONG_SWORD:
                m_weapon = new LongSword(m_row, m_col);
                break;
                
            case Weapon::MAGIC_AXE:
                m_weapon = new MagicAxe(m_row, m_col);
                break;
                
            case Weapon::MAGIC_FANGS:
                m_weapon = new MagicFang(m_row, m_col);
                break;
                
            default:
                break;
        }
    }
    
    return *this;
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

bool Actor::isDead() const {
    return m_dead_status;
}

// Muatators
void Actor::setPosition(int row, int col) {
    if (row < 0 || row >= 18 || col < 0 || col >= 70) {
        return;
    }
    m_row = row;
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

void Actor::setDeadStatus(bool isDead) {
    m_dead_status = isDead;
}

/**
 A dexterity bonus, an integer used in determining whether an attacker using that weapon hits the defender, using the following formula:
 attackerPoints = attackerDexterity + weaponDexterityBonus;
 defenderPoints = defenderDexterity + defenderArmorPoints;
 if (randInt(attackerPoints) >= randInt(defenderPoints))
 attacker has hit defender
 A damage amount, an integer that used in determining how much damage is done to a defender who is hit (i.e., how much the defender's hit points decrease), using the following formula:
 damagePoints = randInt(attackerStrength + weaponDamageAmount);
 */
string Actor::attack(Actor* actor) {
    int attackerPoints = m_dexterity_points + getWeapon()->getDexBonus();
    int defenderPoints = actor->getDexterityPoints() + actor->getArmorPoints();
    string result;
    
    if (randInt(attackerPoints) >= randInt(defenderPoints)) {           // Hit the actor
        int damageAmount = randInt(m_strength_points + getWeapon()->getDamageBonus());
        int hitPoints = actor->getHitPoints();
        if (damageAmount > 0) {
            hitPoints -= damageAmount;
            actor->setHitPoints(hitPoints);
        }
        if (hitPoints <= 0) {
            actor->setDeadStatus(true);
            result = getName() + " " + getWeapon()->getWeaponAction() + " " + getWeapon()->getName()
            + " at " + actor->getName() + " dealing a final blow.";
        } else {
            if (getWeapon()->getWeaponType() == Weapon::MAGIC_FANGS) {
                MagicFang* magicFang = dynamic_cast<MagicFang*>(getWeapon());
                int sleepTime = magicFang->randomSleepTime();
                if (sleepTime > 0) {
                    actor->setSleepTime(max(sleepTime, actor->getSleepTime()));
                    result = getName() + " " + getWeapon()->getWeaponAction() + " " + getWeapon()->getName()
                    + " at " + actor->getName() + " and hits, putting " + actor->getName() + " to sleep.";
                    return result;
                }
            }
            result = getName() + " " + getWeapon()->getWeaponAction() + " " + getWeapon()->getName()
            + " at " + actor->getName() + " and hits.";
        }
    } else {                                                            // Missed
        result = getName() + " " + getWeapon()->getWeaponAction() + " " + getWeapon()->getName() + " at " + actor->getName() + " and misses.";
    }
    return result;
}

void Actor::move(Direction direction) {
    switch (direction) {
        case LEFT:
            m_col--;
            break;
            
        case RIGHT:
            m_col++;
            break;
            
        case UP:
            m_row--;
            break;
            
        case DOWN:
            m_row++;
            break;
            
        default:
            break;
    }
}