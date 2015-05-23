// Game.cpp

#include "Game.h"
#include "utilities.h"
#include <iostream>
using namespace std;

// Implement these and other Game member functions you may have added.

Game::Game(int goblinSmellDistance) {
    
}

void Game::play()
{
//	cout << "Press q to exit game." << endl;
    dungeon.generate();
    dungeon.display();
    cout << "Dungeon Level: " << dungeon.getCurrentLevel() << ", ";
    while (getCharacter() != 'q') {
        
    };
}

// You will presumably add to this project other .h/.cpp files for the
// various classes of objects you need to play the game:  player, monsters,
// weapons, etc.  You might have a separate .h/.cpp pair for each class
// (e.g., Player.h, Boegeyman.h, etc.), or you might put the class
// declarations for all actors in Actor.h, all game objects in GameObject.h,
// etc.
