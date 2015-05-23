// utilities.h

// Note:  YOU MUST NOT MAKE ANY CHANGE TO THIS FILE!

#ifndef UTILITIES_INCLUDED
#define UTILITIES_INCLUDED

const char ARROW_LEFT  = 'h';
const char ARROW_RIGHT = 'l';
const char ARROW_UP    = 'k';
const char ARROW_DOWN  = 'j';

char getCharacter();
void clearScreen();
int randInt(int limit);             // random int from 0 to limit-1
bool trueWithProbability(double p); // return true with probability p

#endif // UTILITIES_INCLUDED
