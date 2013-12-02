#ifndef PLOTTER_H_INCLUDED
#define PLOTTER_H_INCLUDED
#include <windows.h>
#include <mmsystem.h>
#include <conio.h>

const unsigned char SQUARE = 219;
const unsigned char LEFT   = 221;
const unsigned char RIGHT  = 222;
const unsigned char TOP    = 223;
const unsigned char BOTTOM = 220;
const unsigned char BLANK  = ' ';

enum ink
{
    black   = 0x00, darkblue = 0x01, darkgreen  = 0x02, darkcyan  = 0x03,
    darkred = 0x04, purple   = 0x05, darkyellow = 0x06, lightgrey = 0x07,
    grey    = 0x08, blue     = 0x09, green      = 0x0A, cyan      = 0x0B,
    red     = 0x0C, magenta  = 0x0D, yellow     = 0x0E, white     = 0x0F
};

class Plotter
{
    protected:
       COORD  coordScreen;
       HANDLE hConsoleOutput;
       char   dummy;
       void cls( HANDLE hConsole );
    public:
       Plotter();
       void clear();
       void move(int, int);
       void plot(int,int,char);
       void setColor(ink);
};


#endif /*PLOTTER_H_*/
