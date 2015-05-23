// main.cpp

// Note:  YOU MUST NOT MAKE ANY CHANGE TO THIS FILE, except for the argument
// to the Game constructor.

#include "Game.h"
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    // The following call to srand ensures that each time you run the program,
    // you'll get a different series of random numbers generated, and thus
    // different randomly-generated levels, monsters, scrolls, etc.  If you
    // comment out this call, then each game you start will run the same up
    // until you change the way you attack a monster or do something else that
    // will call randInt in a different circumstance than you did before.
    // This repeatability could be useful for debugging.
    
//    srand(static_cast<unsigned int>(time(0)));
    
    // Your program must use whatever value is passed to the Game constructor
    // as the distance a goblin can smell.  The spec stated this is 15.  Some
    // people might implement the recursive goblin algorithm for determining
    // the shortest path to the player in a way that takes an uncomfortably
    // long time for that distance.  If you're one of them, then until you
    // improve your algorithm, pass a value smaller than 15 to the game
    // constructor so your game is comfortable to play.
    
    Game g(15);
    g.play();
}
