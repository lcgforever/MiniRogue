//
//  StairWay.h
//  MiniRogue
//
//  Created by Chenguang Liu on 5/24/15.
//  Copyright (c) 2015 Chenguang Liu. All rights reserved.
//

#ifndef MiniRogue_StairWay_h
#define MiniRogue_StairWay_h

#include "GameObject.h"
class StairWay : public GameObject {
public:
    // constructor
    StairWay(int row, int col) : GameObject("Stair Way", row, col) {}
    
    // Object type
    virtual ObjectType getObjectType() const {
        return STARI_WAY;
    }
    
    virtual char getSymbolOnMap() const {
        return '>';
    }
};

#endif
