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
using namespace std;

class GameObject {
public:
    // constructor
    GameObject (string name) {
        m_name = name;
    }
    
    // Accessor
    virtual string getName() const {
        return m_name;
    }
    
private:
    string m_name;
};

#endif
