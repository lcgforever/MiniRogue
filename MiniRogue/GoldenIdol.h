//
//  GoldenIdol.h
//  MiniRogue
//
//  Created by Chenguang Liu on 5/23/15.
//  Copyright (c) 2015 Chenguang Liu. All rights reserved.
//

#ifndef MiniRogue_GoldenIdol_h
#define MiniRogue_GoldenIdol_h

//
//  GoldenIdol.h
//  MiniRogue
//
//  Created by Sarah Sang on 5/23/15.
//  Copyright (c) 2015 Chenguang Liu. All rights reserved.
//
#include "GameObject.h"
#include <iostream>

class GoldenIdol : public GameObject {
public:
    // constructor
    GoldenIdol(int row, int col) : GameObject("Golden Idol", row, col) {}
    
    // Object type
    virtual ObjectType getObjectType() const {
        return GOLDEN_IDOL;
    }
    
    virtual char getSymbolOnMap() const {
        return '&';
    }
};

#endif //GOLDENIDOL_INCLUDED
