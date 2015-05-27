//
//  GameObject.h
//  MiniRogue
//
//  Created by Chenguang Liu on 5/22/15.
//  Copyright (c) 2015 Chenguang Liu. All rights reserved.
//

#ifndef MiniRogue_GameObject_h
#define MiniRogue_GameObject_h

// This is GameObjects.h
/* This is the base class, from which, we could derive
 weapons class, scroll weapon, golden idol weapon
 */
#include <string>
#include "utilities.h"
using namespace std;

class GameObject {
public:
    // constructor
    GameObject (string name, int row, int col) {
        m_name = name;
        m_row = row;
        m_col = col;
    }
    // Destructor
    virtual ~GameObject() {}
    
    // Accessor
    string getName() const {
        return m_name;
    }
    
    int getRow() const {
        return m_row;
    }
    
    int getCol() const {
        return m_col;
    }
    
    // Object type
    enum ObjectType {
        WEAPON = ')',
        SCROLL = '?',
        STARI_WAY = '>',
        GOLDEN_IDOL = '&'
    };
    
    virtual ObjectType getObjectType() const = 0;
    
    virtual char getSymbolOnMap() const = 0;
    
private:
    int m_row;
    int m_col;
    string m_name;
};

#endif
