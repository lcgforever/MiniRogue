// utilities.cpp

// Note:  YOU MUST NOT MAKE ANY CHANGE TO THIS FILE!

#include "utilities.h"
#include <cstdlib>

  // Return a uniformly distributed random integer from 0 to limit-1 inclusive
int randInt(int limit)
{
    return std::rand() % limit;
}

  // return true with a given probability
bool trueWithProbability(double p)
{
    return rand() < p * RAND_MAX + p; 
}

#ifdef _MSC_VER  //  Microsoft Visual C++

#include <windows.h>
#include <conio.h>

char getCharacter()
{
    int c = _getch();
    if (c != 0xE0  &&  c != 0x00)  // first of the two sent by arrow keys
        return c;
    else
    {
        c = _getch();
        switch (c)
        {
          case 'K':  return ARROW_LEFT;
          case 'M':  return ARROW_RIGHT;
          case 'H':  return ARROW_UP;
          case 'P':  return ARROW_DOWN;
          default:   return '?';
        }
    }
}

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
							&dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not Microsoft Visual C++, so assume UNIX interface

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <termios.h>
using namespace std;

static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal escape sequence:  ESC [
static const char* ESC_SEQ_X = "\xEF\x9C";  // Xcode Console arrow key escape sequence

class TerminalModeSetter
{
  public:
    TerminalModeSetter()
    {
        tcgetattr(STDIN_FILENO, &m_old);
        m_new = m_old;
        m_new.c_lflag &= ~(ICANON | ECHO);
        m_new.c_cc[VMIN] = 1;
        m_new.c_cc[VTIME] = 0;
        tcsetattr(STDIN_FILENO, TCSANOW, &m_new);
    }
    ~TerminalModeSetter()
    {
        tcsetattr(STDIN_FILENO, TCSANOW, &m_old);
    }
  private:
    termios m_old;
    termios m_new;
};

char getCharacter()
{
    static TerminalModeSetter dummy;
    char ch;
    if (!cin.get(ch))
        return '?';
    if (ch != ESC_SEQ[0]  &&  ch != ESC_SEQ_X[0])
        return ch;
    if (!cin.get(ch)  ||  (ch != ESC_SEQ[1]  &&  ch != ESC_SEQ_X[1])  ||  !cin.get(ch))
        return '?';
    switch (ch)
    {
      case 'D': case '\x82':  return ARROW_LEFT;
      case 'C': case '\x83':  return ARROW_RIGHT;
      case 'A': case '\x80':  return ARROW_UP;
      case 'B': case '\x81':  return ARROW_DOWN;
      default:   return '?';
    }
}

void clearScreen()
{
    static const char* term = getenv("TERM");
    if (term == NULL  ||  strcmp(term, "dumb") == 0)
        cout << endl;
     else
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
}

#endif
