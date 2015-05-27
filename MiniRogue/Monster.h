// This is Monster.h
/*
 Monster class is derived from Actor class,
 Bogeyman class, Snakewoman class, Dragon class, Goblin class
 are derived from Monster class
 */


#ifndef MONSTER_INCLUDED
#define MONSTER_INCLUDED

#include "Actor.h"

class Monster : public Actor {
public:
    Monster(string name, int hitPoints, int armorPoints, int strengthPoints, int dexterityPoints, int row, int col) : Actor(name, hitPoints, armorPoints, strengthPoints, dexterityPoints, row, col) {}
    // Destructor
    virtual ~Monster() {}
    
    // Actions
    // Do nothing
    void doNothing() {
        int sleepTime = getSleepTime();
        if (sleepTime > 0) {
            sleepTime--;
            setSleepTime(sleepTime);
        }
        return;
    }
    
    // Monster drops its weapon, if nothing at that position before
    virtual GameObject* droppedItem() const = 0;
    virtual bool canSmellPlayer(Player* player) const = 0;
    virtual char getSymbolOnMap() const = 0;
    
    // Monster type
    enum MonsterType {
        SNAKEWOMAN = 0,
        GOBLIN = 1,
        BOGEYMAN = 2,
        DRAGON = 3,
    };
    
    virtual void regainHitPoints() {
        return;
    }
    
    virtual MonsterType getMonsterType() const = 0;
};

/*
 Bogeyman appears at level 2 or deeper
 */
class Bogeyman : public Monster {
public:
    // constructor
    // Hit points, random from 5 to 10 randInt(6) + 5
    // armor, 2
    // strength, random from 2 to 3 randInt(2) + 2
    // dexterity, random from 2 to 3
    Bogeyman(int row, int col) : Monster("Bogeyman", randInt(6) + 5, 2, randInt(2) + 2, randInt(2) + 2, row, col) {
        // Bogeyman uses short sword
        ShortSword* shortSword = new ShortSword(row, col);
        setWeapon(shortSword);
    }
    
    virtual GameObject* droppedItem() const {
        if (trueWithProbability(0.1)) {
            return new MagicAxe(getRow(), getCol());
        }
        return nullptr;
    }
    // smell penetrate wall and within 5 steps
    virtual bool canSmellPlayer(Player* player) const {
        return ((abs(this->getCol() - player->getCol()) + abs(this->getRow() - player->getRow())) <= 5);
    }
    
    virtual char getSymbolOnMap() const {
        return 'B';
    }
    
    virtual MonsterType getMonsterType() const {
        return BOGEYMAN;
    }
    
private:
    
};

/*
 SnakeWoman could appear on any level
 */
class Snakewoman : public Monster {
public:
    // constructor
    // Hit points, from 3 to 6
    // armor, 3
    // strength 2
    // dexterity 3
    Snakewoman(int row, int col) : Monster("Snakewoman", randInt(4) + 3, 3, 2, 3, row, col) {
        // Snakewoman uses magic funds of sleep
        MagicFang* MagicFang = new class MagicFang(row, col);
        setWeapon(MagicFang);
    }
    
    virtual GameObject* droppedItem() const {
        if (trueWithProbability((double) 1 / 3)) {
            return new class MagicFang(getRow(), getCol());
        }
        return nullptr;
    }
    
    // smell penetrate wall and within 5 steps
    virtual bool canSmellPlayer(Player* player) const {
        return ((abs(this->getCol() - player->getCol()) + abs(this->getRow() - player->getRow())) <= 3);
    }
    
    virtual char getSymbolOnMap() const {
        return 'S';
    }
    
    virtual MonsterType getMonsterType() const {
        return SNAKEWOMAN;
    }
    
private:
    
};

/*
 Dragon appear at level 3 or deeper
 */
class Dragon : public Monster {
public:
    // constructor
    // Hit points form 20 t0 25 randInt(6) + 20
    // Armor 4
    // Strength 4
    // Dexterity 4
    Dragon(int row, int col, int maxHitPoints) : Monster("Dragon", maxHitPoints, 4, 4, 4, row, col) {
        // Dragon uses long sword
        LongSword* LongSword = new class LongSword(row, col);
        setWeapon(LongSword);
        m_max_hit_points = maxHitPoints;
    }
    // destructor
    // Accessor
    // Mutator
    virtual void regainHitPoints() {
        int hitPoints = getHitPoints();
        if (hitPoints == m_max_hit_points) {
            return;
        }
        setHitPoints(hitPoints + 1);
    }
    
    // 100% drop item
    virtual GameObject* droppedItem() const {
        int scrollType = randInt(5);
        switch (scrollType) {
            case Scroll::IMPROVE_ARMOR:
                return new ArmorScroll(getRow(), getCol());
                
            case Scroll::RAISE_STRENGTH:
                return new StrengthScroll(getRow(), getCol());
                
            case Scroll::ENHANCE_HEALTH:
                return new HealthScroll(getRow(), getCol());
                
            case Scroll::ENHANCE_DEXTERITY:
                return new DexterityScroll(getRow(), getCol());
                
            case Scroll::TELEPORTATION:
                return new TeleScroll(getRow(), getCol());
                
            default:
                return nullptr;
        }
    }
    
    virtual bool canSmellPlayer(Player* player) const {
        return false;
    }
    
    virtual char getSymbolOnMap() const {
        return 'D';
    }
    
    virtual MonsterType getMonsterType() const {
        return DRAGON;
    }
    
private:
    int m_max_hit_points;
};

class Goblin : public Monster {
public:
    // constructor
    // Hit Points, from 15 to 20 randInt(6) + 15
    // Armor 1
    // Strength 3
    // Dexterity 1
    Goblin(int row, int col, int smellDistance) : Monster("Goblin", randInt(6) + 15, 1, 3, 1, row, col) {
        // Goblin uses short sword
        ShortSword* shortSword = new ShortSword(row, col);
        setWeapon(shortSword);
        m_smell_distance = smellDistance;
    }
    // destructor
    // Accessor
    // Mutator
    virtual GameObject* droppedItem() const {
        if (trueWithProbability((double) 1 / 3)) {
            if (trueWithProbability(0.5)) {
                return new MagicAxe(getRow(), getCol());
            } else {
                return new MagicFang(getRow(), getCol());
            }
        }
        return nullptr;
    }
    virtual bool canSmellPlayer(Player* player) const {
        return false;
    }
    
    bool isCloseEnoughToPlayer(Player* player) const {
        return ((abs(this->getCol() - player->getCol()) + abs(this->getRow() - player->getRow())) <= m_smell_distance);
    }
    
    virtual char getSymbolOnMap() const {
        return 'G';
    }
    
    virtual MonsterType getMonsterType() const {
        return GOBLIN;
    }
    
private:
    int m_smell_distance;
};

#endif // MONSTER_INCLUDED
