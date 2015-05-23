//
//  Inventory.cpp
//  MiniRogue
//
//  Created by Chenguang Liu on 5/22/15.
//  Copyright (c) 2015 Chenguang Liu. All rights reserved.
//

#include "Inventory.h"

Inventory::~Inventory() {
    for (size_t i = 0; i < items.size(); i++) {
        delete items[i];
    }
}

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

GameObject* Inventory::getItem(char pos) const {
    int charTodigit = static_cast<int> (pos - 'a');
    if (items.size() == 0 || charTodigit < 0 || charTodigit > 25) {
        return nullptr;
    }
    return items[charTodigit];
}

void Inventory::add(GameObject* item) {
    items.push_back(item);
}

void Inventory::remove(char pos) {
    int charTodigit = static_cast<int> (pos - 'a');
    if (items.size() == 0 || charTodigit < 0 || charTodigit > 25) {
        return;
    }
    vector<GameObject*>::iterator p = items.begin();
    int i = 0;
    while(i != charTodigit) {
        p++;
    }
    items.erase(p);
}
