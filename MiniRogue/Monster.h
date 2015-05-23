// This is Monster.h
/*
 Monster class is derived from Actor class,
 Bogeyman class, Snakewoman class, Dragon class, Goblin class
 are derived from Monster class
 */


#ifndef MONSTER_INCLUDED
#define MONSTER_INCLUDED

#include "Actor.h"
#include "utilities.h"

class Monster : public Actor {
public:
    Monster(string name, int hitPoints, int armorPoints, int strengthPoints, int dexterityPoints) : Actor(string name, int hitPoints, int armorPoints, int strengthPoints, int dexterityPoints)
    {}
    // Do nothing
    void doNothing() {
        return;
    }
    // Monster dies
    bool isDead() {
        return (getHitPoints() <= 0);
    }
    // Monster drops its weapon, if nothing at that position before
    Weapon* dropWeapon() {
        return getWeapon();
    }
    // Attack Player
    
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
    Bogeyman() : Monster("Bogeyman", randInt(6) + 5, 2, randInt(2) + 2, randInt(2) + 2) {
        // Bogeyman uses short sword
        ShortSword* shortSword;
        setWeapon(shortSword);
    }
    // destructor
    // Accessor
    // Mutator
    
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
    Snakewoman() : Monster("Snakewoman", randInt(4) + 3, 3, 2, 3) {
        // Snakewoman uses magic funds of sleep
        MagicFang* MagicFang;
        setWeapon(MagicFang)
    }
    // destructor
    // Accessor
    // Mutator
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
    Dragon() : Monster("Dragon", randInt(6) + 20; 4, 4, 4) {
        // Dragon uses long sword
        LongSword* LongSword;
        setWeapon(LongSword);
    }
    // destructor
    // Accessor
    // Mutator
private:
    
};

class Goblin : public Monster {
public:
    // constructor
    // Hit Points, from 15 to 20 randInt(6) + 15
    // Armor 1
    // Strength 3
    // Dexterity 1
    Goblin() : Monster("Goblin", randInt(6) + 15, 1, 3, 1) {
        // Goblin uses short sword
        ShortSword* shortSword;
        setWeapon(shortSword);
    }
    // destructor
    // Accessor
    // Mutator
private:
    
};

#endif // MONSTER_INCLUDED
