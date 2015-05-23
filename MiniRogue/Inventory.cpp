//
//  Inventory.cpp
//  MiniRogue
//
//  Created by Chenguang Liu on 5/22/15.
//  Copyright (c) 2015 Chenguang Liu. All rights reserved.
//

#include "Inventory.h"

void Inventory::display() const {
    cout << "Inventory:" << endl;
    for (int i = 0; i < items.size(); i++) {
        char digitTochar = 'a' + i;
        cout << digitTochar << ". " << items[i]->getName() << endl;
    }
}

size_t Inventory::getItemCount() const {
    return items.size();
}

void Inventory::remove(char num) {
    int charTodigit = static_cast<int> (num - 'a');
    if (charTodigit < 0 || charTodigit > 25) {
        return;
    }
    vector<GameObject*>::iterator p = items.begin();
    int i = 0;
    while(i != charTodigit) {
        p++;
    }
    items.erase(p);
}

void Inventory::add(GameObject* item) {
    if (items.size() >= 26) {
        return;
    }
    items.push_back(item);
}
