//
//  Dungeon.h
//  MiniRogue
//
//  Created by Chenguang Liu on 5/22/15.
//  Copyright (c) 2015 Chenguang Liu. All rights reserved.
//

#ifndef __MiniRogue__Dungeon__
#define __MiniRogue__Dungeon__

#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include "utilities.h"
#include "GameObject.h"
#include "Actor.h"
#include "GoldenIdol.h"
#include "StairWay.h"
#include "Scroll.h"
#include "Player.h"
#include "Monster.h"
using namespace std;

class Dungeon {
public:
    Dungeon(int goblinSmellDistance);
    ~Dungeon();
    
    // Accessor
    Player* getPlayer() const;
    int getCurrentLevel() const;
    
    void generate();
    void movePlayer(Actor::Direction direction);
    void pickUpIfThereIsItem();
    void goToNextLevelIfOnStair();
    void teleportPlayer();
    void addMessage(string message);
    void update();
    void display();
    
private:
    struct Point {
        int row;
        int col;
    };
    
    struct Room {
        Point topLeft;
        Point topRight;
        Point bottomLeft;
        Point bottomRight;
        int length;
        int height;
    };
    
    struct comparator {
        bool operator() (Room i, Room j) {
            return (i.topLeft.col < j.topLeft.col);
        }
    } compareRoomLeftEdge;
    
    bool isRoomOverlap(Room r1, Room r2) const;
    void generateRoomsAndCorridors();
    // move Monster, this should be private function
    void moveMonster(Monster* monster);
    Actor::Direction* getMonsterMoveDirection(Monster* monster);
    bool directionNotBlocked(Actor::Direction movingdirection, Monster* monster);
    bool posNotBlocked(int row, int col);
    int goblinFindPath(int row, int col, int step);
    bool posValid(int row, int col);
    
    enum MapType {
        WALL = '#',
        EMPTY = ' ',
        GOLDEN_IDOL = '&',
        STAIR_WAY = '>',
        WEAPON = ')',
        SCROLL = '?',
        PLAYER = '@',
        BOGEYMAN = 'B',
        SNAKEWOMAN = 'S',
        DRAGON = 'D',
        GOBLIN = 'G'
    };
    char m_map[18][70];
    bool m_marked[18][70];
    unordered_map<int, bool> m_occupied_positions;
    unordered_map<int, GameObject*> m_object_map;
    unordered_map<int, Monster*> m_monster_map;
    vector<string> m_messages;
    int m_current_level;
    int m_goblin_smell_distance;
    Actor::Direction m_goblin_move_direction;
    Player* m_player;
};

#endif /* defined(__MiniRogue__Dungeon__) */
