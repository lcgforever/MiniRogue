//
//  Player.cpp
//  MiniRogue
//
//  Created by Chenguang Liu on 5/22/15.
//  Copyright (c) 2015 Chenguang Liu. All rights reserved.
//

#include "Player.h"

// Constructor
Player::Player(int row, int col) : Actor("Player", 20, 2, 2, 2, row, col) {
    ShortSword* shortSword = new ShortSword(row, col);
    setWeapon(shortSword);
    ShortSword* copy = new ShortSword(row, col);
    m_inventory.add(copy);
    getGoldenIdol = false;
    m_max_hit_points = 20;
}

// Copy constructor
Player::Player(const Player& other) : Actor(other) {
    m_inventory = other.m_inventory;
    m_max_hit_points = other.m_max_hit_points;
    getGoldenIdol = other.getGoldenIdol;
}

// Assignment operator
Player& Player::operator=(const Player& other) {
    if (this != &other) {
        Actor::operator=(other);
        m_inventory = other.m_inventory;
        m_max_hit_points = other.m_max_hit_points;
        getGoldenIdol = other.getGoldenIdol;
    }
    
    return *this;
}

bool Player::canPickUpItem() const {
    return m_inventory.getItemCount() < 26;
}

bool Player::canGetItemByPos(char pos) const {
    int charToDigit = pos - 'a';
    return charToDigit >= 0 && charToDigit < m_inventory.getItemCount();
}

bool Player::pickedUpGoldenIdol() const {
    return getGoldenIdol;
}

// Mutators
void Player::setMaxHitPoints(int points) {
    m_max_hit_points = points;
}

void Player::setPickedUpGoldenIdol() {
    getGoldenIdol = true;
}

// Actions
void Player::pickUpItem(char objectType, GameObject* item) {
    switch (objectType) {
        case GameObject::WEAPON: {
            Weapon* weapon = dynamic_cast<Weapon*>(item);
            switch (weapon->getWeaponType()) {
                case Weapon::MACE:
                    m_inventory.add(dynamic_cast<Mace*>(weapon));
                    break;
                    
                case Weapon::SHORT_SWORD:
                    m_inventory.add(dynamic_cast<ShortSword*>(weapon));
                    break;
                    
                case Weapon::LONG_SWORD:
                    m_inventory.add(dynamic_cast<LongSword*>(weapon));
                    break;
                    
                case Weapon::MAGIC_AXE:
                    m_inventory.add(dynamic_cast<MagicAxe*>(weapon));
                    break;
                    
                case Weapon::MAGIC_FANGS:
                    m_inventory.add(dynamic_cast<MagicFang*>(weapon));
                    break;
                    
                default:
                    break;
            }
            break;
        }
            
        case GameObject::SCROLL: {
            Scroll* scroll = dynamic_cast<Scroll*>(item);
            switch (scroll->getScrollType()) {
                case Scroll::IMPROVE_ARMOR:
                    m_inventory.add(dynamic_cast<ArmorScroll*>(scroll));
                    break;
                    
                case Scroll::RAISE_STRENGTH:
                    m_inventory.add(dynamic_cast<StrengthScroll*>(scroll));
                    break;
                    
                case Scroll::ENHANCE_HEALTH:
                    m_inventory.add(dynamic_cast<HealthScroll*>(scroll));
                    break;
                    
                case Scroll::ENHANCE_DEXTERITY:
                    m_inventory.add(dynamic_cast<DexterityScroll*>(scroll));
                    break;
                    
                case Scroll::TELEPORTATION:
                    m_inventory.add(dynamic_cast<TeleScroll*>(scroll));
                    break;
                    
                default:
                    break;
            }
            break;
        }
            
        default:
            break;
    }
}

string Player::wieldWeapon(char pos) {
    GameObject* gameObject = m_inventory.getItem(pos);
    string name = gameObject->getName();
    if (gameObject->getObjectType() != GameObject::WEAPON) {
        return "You can't wield a " + name + ".";
    }
    
    delete getWeapon();
    Weapon* newWeapon = dynamic_cast<Weapon*>(gameObject);
    Weapon* copy;
    switch (newWeapon->getWeaponType()) {
        case Weapon::MACE:
            copy = new Mace(getRow(), getCol());
            setWeapon(copy);
            break;
            
        case Weapon::SHORT_SWORD:
            copy = new ShortSword(getRow(), getCol());
            setWeapon(copy);
            break;
            
        case Weapon::LONG_SWORD:
            copy = new LongSword(getRow(), getCol());
            setWeapon(copy);
            break;
            
        case Weapon::MAGIC_AXE:
            copy = new MagicAxe(getRow(), getCol());
            setWeapon(copy);
            break;
            
        case Weapon::MAGIC_FANGS:
            copy = new MagicFang(getRow(), getCol());
            setWeapon(copy);
            break;
            
        default:
            break;
    }
    return "You are wielding " + name + ".";
}

// Return true if the player read a teleportation scroll
string Player::readScroll(char pos) {
    GameObject* gameObject = m_inventory.getItem(pos);
    string name = gameObject->getName();
    if (gameObject->getObjectType() != GameObject::SCROLL) {
        return "You can't read a " + name + ".";
    }
    Scroll* scroll = dynamic_cast<Scroll*>(gameObject);
    string result = "You read a scroll called " + name + ".\n";
    switch (scroll->getScrollType()) {
        case Scroll::IMPROVE_ARMOR:
            setArmorPoints(getArmorPoints() + scroll->getUpgradePoints());
            return result + "Your armor glows blue.";
            
        case Scroll::RAISE_STRENGTH:
            setStrengthPoints(getArmorPoints() + scroll->getUpgradePoints());
            return result + "Your muscles bulge.";
            
        case Scroll::ENHANCE_HEALTH:
            m_max_hit_points += scroll->getUpgradePoints();
            return result + "You feel your heart beating stronger.";
            
        case Scroll::ENHANCE_DEXTERITY:
            setDexterityPoints(getDexterityPoints() + scroll->getUpgradePoints());
            return result + "You feel like less of a klutz.";
            
        case Scroll::TELEPORTATION:
            // Let the dungeon take care of teleporting
            return result + "You feel your body wrenched in space and time.";
            
        default:
            break;
    }
    m_inventory.remove(pos);
    return "";
}

void Player::regainHitPoints() {
    int hitPoints = getHitPoints();
    if (hitPoints == m_max_hit_points) {
        return;
    }
    setHitPoints(hitPoints + 1);
}

void Player::openInventory() {
    m_inventory.display();
}