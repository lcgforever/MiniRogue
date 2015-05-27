//
//  Dungeon.cpp
//  MiniRogue
//
//  Created by Chenguang Liu on 5/22/15.
//  Copyright (c) 2015 Chenguang Liu. All rights reserved.
//

#include "Dungeon.h"

Dungeon::Dungeon(int goblinSmellDistance) {
    m_current_level = 0;
    m_player = new Player(0, 0);
    m_goblin_smell_distance = goblinSmellDistance;
}

Dungeon::~Dungeon() {
    for (unordered_map<int, GameObject*>::iterator it = m_object_map.begin(); it != m_object_map.end(); ++it) {
        delete it->second;
    }
    for (unordered_map<int, Monster*>::iterator it = m_monster_map.begin(); it != m_monster_map.end(); ++it) {
        delete it->second;
    }
}

Player* Dungeon::getPlayer() const {
    return m_player;
}

int Dungeon::getCurrentLevel() const {
    return m_current_level;
}

bool Dungeon::isRoomOverlap(Room r1, Room r2) const {
    // If one room is on left side of other
    if (r1.topLeft.col > r2.bottomRight.col + 1 || r2.topLeft.col > r1.bottomRight.col + 1)
        return false;
    
    // If one room is above other
    if (r1.topLeft.row > r2.bottomRight.row + 1 || r2.topLeft.row > r1.bottomRight.row + 1)
        return false;
    
    return true;
}

void Dungeon::generateRoomsAndCorridors() {
    // Generate rooms
    int roomNum = randInt(4) + 2;
    vector<Room> roomList;
    Room newRoom;
    Point topLeft, topRight, bottomLeft, bottomRight;
    int roomLength, roomHeight;
    int roomCount = 0;
    while (roomCount < roomNum) {
        roomLength = randInt(26) + 5 + m_current_level;
        roomHeight = randInt(6) + 3;
        topLeft.col = randInt(69 - roomLength) + 1;
        topLeft.row = randInt(17 - roomHeight) + 1;
        topRight.row = topLeft.row;
        topRight.col = topLeft.col + roomLength - 1;
        bottomLeft.col = topLeft.col;
        bottomLeft.row = topLeft.row + roomHeight - 1;
        bottomRight.col = topRight.col;
        bottomRight.row = topRight.row + roomHeight - 1;
        newRoom.topLeft = topLeft;
        newRoom.topRight = topRight;
        newRoom.bottomLeft = bottomLeft;
        newRoom.bottomRight = bottomRight;
        newRoom.length = roomLength;
        newRoom.height = roomHeight;
        
        bool isOverlap = false;
        for (size_t i = 0; i < roomList.size(); i++) {
            if (isRoomOverlap(newRoom, roomList[i])) {
                isOverlap = true;
                break;
            }
        }
        if (isOverlap) {
            continue;
        } else {
            roomList.push_back(newRoom);
            roomCount++;
            for (int r = newRoom.topLeft.row; r <= newRoom.bottomLeft.row; r++) {
                for (int c = newRoom.topLeft.col; c <= newRoom.topRight.col; c++) {
                    m_occupied_positions[r * 70 + c] = true;
                }
            }
        }
    }
    
    std::sort(roomList.begin(), roomList.end(), compareRoomLeftEdge);
    // Generate corridors
    Room currentRoom, nextRoom;
    int row1, col1, row2, col2, minRow, maxRow, turnCol;
    for (int i = 0; i < roomCount - 1; i++) {
        currentRoom = roomList[i];
        nextRoom = roomList[i + 1];
        col1 = currentRoom.topRight.col;
        row1 = randInt(currentRoom.height) + currentRoom.topLeft.row;
        col2 = nextRoom.topLeft.col;
        row2 = randInt(nextRoom.height) + nextRoom.topLeft.row;
        minRow = min(row1, row2);
        maxRow = max(row1, row2);
        
        if (col1 <= col2) {
            turnCol = randInt(col2 - col1 + 1) + col1;
            for (int j = col1; j <= turnCol; j++) {
                m_occupied_positions[row1 * 70 + j] = true;
            }
            for (int j = minRow; j <= maxRow; j++) {
                m_occupied_positions[j * 70 + turnCol] = true;
            }
            for (int j = turnCol; j <= col2; j++) {
                m_occupied_positions[row2 * 70 + j] = true;
            }
        } else {
            turnCol = randInt(col1 - col2 + 1) + col2;
            for (int j = col2; j <= turnCol; j++) {
                m_occupied_positions[row2 * 70 + j] = true;
            }
            for (int j = minRow; j <= maxRow; j++) {
                m_occupied_positions[j * 70 + turnCol] = true;
            }
            for (int j = turnCol; j <= col1; j++) {
                m_occupied_positions[row1 * 70 + j] = true;
            }
        }
    }
}

void Dungeon::generate() {
    int r, c, objectCount, pos;
    
    m_occupied_positions.clear();
    generateRoomsAndCorridors();
    // Generate walls and rooms
    for (r = 0; r < 18; r++) {
        for (c = 0; c < 70; c++) {
            m_map[r][c] = (m_occupied_positions[r * 70 + c] ? EMPTY : WALL);
        }
    }
    
    m_occupied_positions.clear();
    // Generate 2 or 3 objects (Weapons or scrolls) and the stairway or golden idol
    objectCount = trueWithProbability(0.5) ? 2 : 3;
    for (int i = 0; i < objectCount + 1; i++) {
        do {
            r = randInt(16) + 1;
            c = randInt(68) + 1;
        } while (m_map[r][c] == WALL || m_occupied_positions.find(r * 70 + c) != m_occupied_positions.end());
        pos = r * 70 + c;
        m_occupied_positions[pos] = true;
        if (i == 0) {
            if (m_current_level == 4) {
                m_map[r][c] = GOLDEN_IDOL;
                GoldenIdol* goldenIdol = new GoldenIdol(r, c);
                m_object_map[pos] = goldenIdol;
            } else {
                m_map[r][c] = STAIR_WAY;
                StairWay* stairWay = new StairWay(r, c);
                m_object_map[pos] = stairWay;
            }
        } else {
            bool generateWeapon = trueWithProbability(0.5);
            if (generateWeapon) {
                m_map[r][c] = WEAPON;
                int weaponType = randInt(3);
                switch (weaponType) {
                    case Weapon::MACE: {
                        Mace* mace = new Mace(r, c);
                        m_object_map[pos] = mace;
                        break;
                    }
                        
                    case Weapon::SHORT_SWORD: {
                        ShortSword* shortSword = new ShortSword(r, c);
                        m_object_map[pos] = shortSword;
                        break;
                    }
                        
                    case Weapon::LONG_SWORD: {
                        LongSword* longSword = new LongSword(r, c);
                        m_object_map[pos] = longSword;
                        break;
                    }
                        
                    default:
                        break;
                }
            } else {
                m_map[r][c] = SCROLL;
                int scrollType = randInt(4);
                switch (scrollType) {
                    case Scroll::IMPROVE_ARMOR: {
                        ArmorScroll* armorScroll = new ArmorScroll(r, c);
                        m_object_map[pos] = armorScroll;
                        break;
                    }
                        
                    case Scroll::RAISE_STRENGTH: {
                        StrengthScroll* strengthScroll = new StrengthScroll(r, c);
                        m_object_map[pos] = strengthScroll;
                        break;
                    }
                        
                    case Scroll::ENHANCE_HEALTH: {
                        HealthScroll* healthScroll = new HealthScroll(r, c);
                        m_object_map[pos] = healthScroll;
                        break;
                    }
                        
                    case Scroll::ENHANCE_DEXTERITY: {
                        DexterityScroll* dexterityScroll = new DexterityScroll(r, c);
                        m_object_map[pos] = dexterityScroll;
                        break;
                    }
                        
                    default:
                        break;
                }
            }
        }
    }
    
    m_occupied_positions.clear();
    // Generate 2 + randInt(5*(L+1)) monsters and the player
    objectCount = 2 + randInt(5 * (m_current_level + 1));
    for (int i = 0; i < objectCount + 1; i++) {
        do {
            r = randInt(16) + 1;
            c = randInt(68) + 1;
        } while (m_map[r][c] == WALL || m_occupied_positions.find(r * 70 + c) != m_occupied_positions.end());
        pos = r * 70 + c;
        m_occupied_positions[pos] = true;
        if (i == 0) {
            m_map[r][c] = PLAYER;
            m_player->setPosition(r, c);
        } else {
            int monsterType;
            if (m_current_level >= 3) {
                monsterType = randInt(4);
            } else if (m_current_level == 2) {
                monsterType = randInt(3);
            } else {
                monsterType = randInt(2);
            }
            switch (monsterType) {
                case Monster::SNAKEWOMAN: {
                    Snakewoman* snakewoman = new Snakewoman(r, c);
                    m_monster_map[pos] = snakewoman;
                    m_map[r][c] = SNAKEWOMAN;
                    break;
                }
                    
                case Monster::GOBLIN: {
                    Goblin* goblin = new Goblin(r, c, m_goblin_smell_distance);
                    m_monster_map[pos] = goblin;
                    m_map[r][c] = GOBLIN;
                    break;
                }
                    
                case Monster::BOGEYMAN: {
                    Bogeyman* bogeyman = new Bogeyman(r, c);
                    m_monster_map[pos] = bogeyman;
                    m_map[r][c] = BOGEYMAN;
                    break;
                }
                    
                case Monster::DRAGON: {
                    Dragon* dragon = new Dragon(r, c, randInt(6) + 20);
                    m_monster_map[pos] = dragon;
                    m_map[r][c] = DRAGON;
                    break;
                }
                    
                default:
                    break;
            }
        }
    }
}

void Dungeon::movePlayer(Actor::Direction direction) {
    if (m_player->getSleepTime() > 0) {
        m_player->setSleepTime(m_player->getSleepTime() - 1);
        return;
    }
    
    int row = m_player->getRow();
    int col = m_player->getCol();
    int newRow, newCol, newPos;
    
    switch (direction) {
        case Actor::LEFT:
            newRow = row;
            newCol = col - 1;
            break;
            
        case Actor::RIGHT:
            newRow = row;
            newCol = col + 1;
            break;
            
        case Actor::UP:
            newRow = row - 1;
            newCol = col;
            break;
            
        case Actor::DOWN:
            newRow = row + 1;
            newCol = col;
            break;
            
        default:
            break;
    }
    newPos = newRow * 70 + newCol;
    
    if (m_map[newRow][newCol] == WALL) {
        return;
    } else if (m_monster_map.find(newPos) != m_monster_map.end()) {
        char c = m_map[newRow][newCol];
        Monster* attackedMonster = m_monster_map[newPos];
        //        m_messages.push_back("AttackedActor name is " + attackedMonster->getName());
        string attackResult;
        switch (c) {
            case BOGEYMAN:
                attackResult = m_player->attack(dynamic_cast<Bogeyman*>(attackedMonster));
                break;
                
            case SNAKEWOMAN:
                attackResult = m_player->attack(dynamic_cast<Snakewoman*>(attackedMonster));
                break;
                
            case DRAGON:
                attackResult = m_player->attack(dynamic_cast<Dragon*>(attackedMonster));
                break;
                
            case GOBLIN:
                attackResult = m_player->attack(dynamic_cast<Goblin*>(attackedMonster));
                break;
                
            default:
                break;
        }
        if (attackedMonster->isDead()) {
            m_map[newRow][newCol] = EMPTY;
            GameObject* gameObject = attackedMonster->droppedItem();
            if (m_object_map.find(newPos) == m_object_map.end() && gameObject != nullptr) {
                m_object_map[newPos] = gameObject;
            }
            delete attackedMonster;
            m_monster_map.erase(newPos);
        }
        m_messages.push_back(attackResult);
    } else {
        m_map[row][col] = EMPTY;
        m_player->move(direction);
        m_map[newRow][newCol] = PLAYER;
    }
}

// If picked up the golden idol, return true; otherwise return false
void Dungeon::pickUpIfThereIsItem() {
    int row = m_player->getRow();
    int col = m_player->getCol();
    int pos = row * 70 + col;
    if (m_object_map.find(pos) != m_object_map.end()) {
        GameObject* gameObject = m_object_map[pos];
        switch (gameObject->getObjectType()) {
            case GameObject::STARI_WAY:
                break;
                
            case GameObject::GOLDEN_IDOL: {
                if (m_player->canPickUpItem()) {
                    m_player->setPickedUpGoldenIdol();
                    m_messages.push_back("Congratulations, you won!");
                    m_messages.push_back("Press q to exit game.");
                } else {
                    m_messages.push_back("Your knapsack is full; you can't pick that up.");
                }
                break;
            }
                
            case GameObject::WEAPON: {
                if (m_player->canPickUpItem()) {
                    m_player->pickUpItem(GameObject::WEAPON, gameObject);
                    m_object_map.erase(pos);
                    m_messages.push_back("You picked up a " + gameObject->getName());
                } else {
                    m_messages.push_back("Your knapsack is full; you can't pick that up.");
                }
                break;
            }
                
            case GameObject::SCROLL: {
                if (m_player->canPickUpItem()) {
                    m_player->pickUpItem(GameObject::SCROLL, gameObject);
                    m_object_map.erase(pos);
                    m_messages.push_back("You picked up a scroll called " + gameObject->getName());
                } else {
                    m_messages.push_back("Your knapsack is full; you can't pick that up.");
                }
                break;
            }
                
            default:
                break;
        }
    }
}

void Dungeon::goToNextLevelIfOnStair() {
    int row = m_player->getRow();
    int col = m_player->getCol();
    int pos = row * 70 + col;
    if (m_object_map.find(pos) != m_object_map.end() && m_object_map[pos]->getObjectType() == GameObject::STARI_WAY) {
        m_current_level++;
        m_object_map.clear();
        m_monster_map.clear();
        m_occupied_positions.clear();
        generate();
        display();
    } else {
        return;
    }
}

void Dungeon::teleportPlayer() {
    int newRow, newCol;
    do {
        newRow = 5 + randInt(8);
        newCol = 10 + randInt(50);
    } while (m_monster_map.find(newRow * 70 + newCol) != m_monster_map.end());
    
    m_player->setPosition(newRow, newCol);
}

// move Monster, this should be private function
void Dungeon::moveMonster(Monster* monster) {
    int row = monster->getRow();
    int col = monster->getCol();
    switch(monster->getMonsterType()) {
        case Monster::BOGEYMAN: {
            if (monster->canSmellPlayer(m_player)) {
                Actor::Direction* dir = getMonsterMoveDirection(monster);
                if (directionNotBlocked(*dir, monster)) {
                    monster->move(*dir);
                }
                else if (directionNotBlocked(*(dir + 1), monster)) {
                    monster->move(*(dir + 1));
                }
                else {
                    monster->doNothing();
                }
            }
            // bogeyman cannot smell player
            else {
                monster->doNothing();
            }
            break;
        }
            
        case Monster::SNAKEWOMAN: {
            if (monster->canSmellPlayer(m_player)) {
                Actor::Direction* dir = getMonsterMoveDirection(monster);
                if (directionNotBlocked(*dir, monster)) {
                    monster->move(*dir);
                }
                else if (directionNotBlocked(*(dir + 1), monster)) {
                    monster->move(*(dir + 1));
                }
                else {
                    monster->doNothing();
                }
            }
            // snakewoman cannot smell palyer
            else {
                monster->doNothing();
            }
            break;
        }
         
        // Dragon does not move
        case Monster::DRAGON:
            break;
            
        // Goblin will take optimal move if can reach player
        case Monster::GOBLIN:
            Goblin* goblin = dynamic_cast<Goblin*>(monster);
            // We only calculate if the goblin is close enough to player, which means rowDiff + colDiff <= smellDistance
            if (goblin->isCloseEnoughToPlayer(m_player)) {
                m_goblin_move_direction = Actor::NOWHERE;
                goblinFindPath(row, col, 0);
                if (m_goblin_move_direction == Actor::NOWHERE) {
                    monster->doNothing();
                } else {
                    monster->move(m_goblin_move_direction);
                }
            }
            break;
    }
    // Mark this monster as moved in the map for later update in its position
    if (monster->getRow() != row || monster->getCol() != col) {
        int pos = row * 70 + col;
        m_occupied_positions[pos] = true;
        if (m_object_map.find(pos) != m_object_map.end()) {
            m_map[row][col] = m_object_map[pos]->getObjectType();
        } else {
            m_map[row][col] = EMPTY;
        }
        m_map[monster->getRow()][monster->getCol()] = monster->getSymbolOnMap();
    }
}

// Get the potential moving direction for Bogeyman and Snakewoman
Actor::Direction* Dungeon::getMonsterMoveDirection(Monster* monster) {
    Actor::Direction* dir = new Actor::Direction[2];
    dir[0] = Actor::NOWHERE;
    dir[1] = Actor::NOWHERE;
    
    // Monster is to the left of Player
    if (monster->getCol() < m_player->getCol()) {
        dir[0] = Actor::RIGHT;
        // Monster is above the player
        if (monster->getRow() < m_player->getRow()) {
            dir[1] = Actor::DOWN;
        }
        // Monster is below the player
        else if (monster->getRow() > m_player->getRow()) {
            dir[1] = Actor::UP;
        }
    }
    // Monster is to the right of the Player
    else if (monster->getCol() > m_player->getCol()) {
        dir[0] = Actor::LEFT;
        // Monster is above the player
        if (monster->getRow() < m_player->getRow()) {
            dir[1] = Actor::DOWN;
        }
        // Monster is below the player
        else if (monster->getRow() > m_player->getRow()) {
            dir[1] = Actor::UP;
        }
    }
    // Monster is in the same col as player
    else {
        // Monster is above the player
        if (monster->getRow() < m_player->getRow()) {
            dir[0] = Actor::DOWN;
        }
        // Monster is below the player
        else if (monster->getRow() > m_player->getRow()) {
            dir[0] = Actor::UP;
        }
    }
    return dir;
}

// Check if the moving direction is not blocked for this monster
bool Dungeon::directionNotBlocked(Actor::Direction movingdirection, Monster* monster) {
    if (movingdirection == Actor::NOWHERE) {
        return false;
    }
    else if (movingdirection == Actor::LEFT) {
        return posNotBlocked(monster->getRow(), monster->getCol() - 1);
    }
    else if (movingdirection == Actor::RIGHT) {
        return posNotBlocked(monster->getRow(), monster->getCol() + 1);
    }
    else if (movingdirection == Actor::UP) {
        return posNotBlocked(monster->getRow() - 1, monster->getCol());
    }
    else {
        return posNotBlocked(monster->getRow() + 1, monster->getCol());
    }
}

// Check if the position is valid for Bogeyman and Snakewoman
bool Dungeon::posNotBlocked(int row, int col) {
    if (row < 0 || col < 0 || row >= 18 || col >= 70) {
        return false;
    }
    else if (m_map[row][col] == ' ' || m_map[row][col] == ')' ||
             m_map[row][col] == '?' || m_map[row][col] == '>' || m_map[row][col] == '&') {
        return true;
    }
    else {
        return false;
    }
}

int Dungeon::goblinFindPath(int row, int col, int step) {
    // Get to the player's position
    if (row == m_player->getRow() && col == m_player->getCol()) {
        return step;
    }
    // Exceed the max smell distance, return a value larger than it
    if (step == m_goblin_smell_distance) {
        return m_goblin_smell_distance + 1;
    }
    // Initialize the four direction path to be larger than max smell distance
    int left = m_goblin_smell_distance + 1, right = m_goblin_smell_distance + 1;
    int up = m_goblin_smell_distance + 1, down = m_goblin_smell_distance + 1;
    
    // Mark this position as visited
    m_marked[row][col] = true;
    
    // Go left and get the path length
    if (posValid(row, col - 1)) {
        left = goblinFindPath(row, col - 1, step + 1);
    }
    // Go right and get the path length
    if (posValid(row, col + 1)) {
        right = goblinFindPath(row, col + 1, step + 1);
    }
    // Go up and get the path length
    if (posValid(row - 1, col)) {
        up = goblinFindPath(row - 1, col, step + 1);
    }
    // Go down and get the path length
    if (posValid(row + 1, col)) {
        down = goblinFindPath(row + 1, col, step + 1);
    }
    
    // Mark this position as unvisited after the traverse
    m_marked[row][col] = false;
    
    // Get the minimum distance among the four directions
    int minDistance = min(left, min(right, min(up, down)));
    
    // If minimum distance is still larger than smell distance, the goblin cannot reach player
    // Otherwise it can reach, go with the optimal direction which is the minimum distance
    if (minDistance > m_goblin_smell_distance) {
        m_goblin_move_direction = Actor::NOWHERE;
    } else {
        if (minDistance == left) {
            m_goblin_move_direction = Actor::LEFT;
        } else if (minDistance == right) {
            m_goblin_move_direction = Actor::RIGHT;
        } else if (minDistance == up) {
            m_goblin_move_direction = Actor::UP;
        } else {
            m_goblin_move_direction = Actor::DOWN;
        }
    }
    
    // Return the minimum distance for recursion
    return minDistance;
}

// Check if the position is valid for Goblin
bool Dungeon::posValid(int row, int col) {
    if (row < 0 || col < 0 || row >= 18 || col >= 70 || m_marked[row][col]) {
        return false;
    }
    else if (m_map[row][col] == ' ' || m_map[row][col] == ')' || m_map[row][col] == '@' ||
             m_map[row][col] == '?' || m_map[row][col] == '>' || m_map[row][col] == '&') {
        return true;
    }
    else {
        return false;
    }
}

void Dungeon::addMessage(string message) {
    m_messages.push_back(message);
}

void Dungeon::update() {
    int row, col;
    Monster* monster;
    GameObject* gameObject;
    for (unordered_map<int, GameObject*>::iterator it = m_object_map.begin(); it != m_object_map.end(); ++it) {
        gameObject = it->second;
        row = gameObject->getRow();
        col = gameObject->getCol();
        m_map[row][col] = gameObject->getObjectType();
    }
    
    m_occupied_positions.clear();
    for (unordered_map<int, Monster*>::iterator it = m_monster_map.begin(); it != m_monster_map.end(); ++it) {
        monster = it->second;
        // Though we call regainHitPoints for all monsters, only dragon take effects
        monster->regainHitPoints();
        row = monster->getRow();
        col = monster->getCol();
        int rowDiff = abs(row - m_player->getRow());
        int colDiff = abs(col - m_player->getCol());
        if (monster->getSleepTime() == 0) {
            if (rowDiff + colDiff <= 1) {
                string result = monster->attack(m_player);
                m_messages.push_back(result);
                if (m_player->isDead()) {
                    m_messages.push_back("You are dead. Game Over!\nPress q to exit Game.");
                    return;
                }
                m_map[row][col] = monster->getSymbolOnMap();
            } else {
                moveMonster(monster);
            }
        }
    }
    
    // Recalculate the positions of moved monsters in the map and change the monster_map key for them
    for (unordered_map<int, bool>::iterator it = m_occupied_positions.begin(); it != m_occupied_positions.end(); ++it) {
        if (it->second) {
            monster = m_monster_map[it->first];
            int newRow = monster->getRow();
            int newCol = monster->getCol();
            m_monster_map.erase(it->first);
            m_monster_map[newRow * 70 + newCol] = monster;
        }
    }
    
    // Place the player
    m_map[m_player->getRow()][m_player->getCol()] = PLAYER;
}

void Dungeon::display() {
    clearScreen();
    for (int r = 0; r < 18; r++) {
        for (int c = 0; c < 70; c++) {
            cout << m_map[r][c];
        }
        cout << endl;
    }
    cout << "Dungeon Level: " << m_current_level << ", Hit points: " << m_player->getHitPoints()
    << ", Armor: " << m_player->getArmorPoints() << ", Strength: " << m_player->getStrengthPoints()
    << ", Dexterity: " << m_player->getDexterityPoints() << endl << endl;
    
    for (vector<string>::const_iterator it = m_messages.begin(); it != m_messages.end(); ++it) {
        cout << *it << endl;
    }
    m_messages.clear();
}
