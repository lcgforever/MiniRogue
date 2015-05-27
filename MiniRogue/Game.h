// Game.h

#ifndef GAME_INCLUDED
#define GAME_INCLUDED

// You may add data members and other member functions to this class.
#include "Dungeon.h"

class Game {
public:
    Game(int goblinSmellDistance);
    ~Game();
    
    void play();
    
private:
    Dungeon* m_dungeon;
    Player* m_player;
};

#endif // GAME_INCLUDED
