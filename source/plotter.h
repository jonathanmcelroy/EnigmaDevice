/*
    Author: CSI 1430, Jonathan McElroy,Aaron Salinas, Elise Brown
    FileName: Plotter.h
    Description: the header file for the plotter object that
    controls the console output display
*/

#ifndef PLOTTER_H_INCLUDED
#define PLOTTER_H_INCLUDED
#include <windows.h>
#include <mmsystem.h>
#include <conio.h>

/*
    These unsigned characters represent
    the given shapes and positions that
    the cursor can have
*/
const unsigned char SQUARE = 219;
const unsigned char LEFT   = 221;
const unsigned char RIGHT  = 222;
const unsigned char TOP    = 223;
const unsigned char BOTTOM = 220;
const unsigned char BLANK  = ' ';

/*
    Ink is an enumerated data type that holds the basic
    colors that plotter can display
*/
enum ink
{
    black   = 0x00, darkblue = 0x01, darkgreen  = 0x02, darkcyan  = 0x03,
    darkred = 0x04, purple   = 0x05, darkyellow = 0x06, lightgrey = 0x07,
    grey    = 0x08, blue     = 0x09, green      = 0x0A, cyan      = 0x0B,
    red     = 0x0C, magenta  = 0x0D, yellow     = 0x0E, white     = 0x0F
};

/*
    Plotter is a class that controls where the cursor is at any given moment
    Plotter can display characters and images to the output screen by controlling
    the cursor.
*/
class Plotter
{
    protected:
       COORD  coordScreen;
       HANDLE hConsoleOutput;
       char   dummy;
       void cls( HANDLE hConsole );
    public:
    
       /*
            Name:   Default Constructor
            Description: Creates a new plotter 
            Arguments: none
            Return Type: technically returns nothing
            but a new plotter is created as a result of this
            method
       */
       Plotter();
       
       /*
            Name: clear
            Description: Clears the plotter reverting it to a
            blank screen
            Arguments: none
            Return Type: void, it changes the plotter internally
            thus no data type needs to be returned
       */
       void clear();
       
       /*
            Name: move
            Description: moves the cursor on the plotter
            to a position specified by the two ints passed into the funciton
            Arguments: The method needs two ints as arguments; these integers
            represent the coordinates on the screen
            Return Type: void, the method changes the plotters cursor position
            so no data type needs to be returned
       */
       void move(int, int);
       
       /*
            Name: plot
            Description: prints a specified character to the screen.
            The plotter moves the cursor to a positon specified by the
            user and prints the char c at that position
            Arguments: two ints and a char.  The ints represent a
            coordinate location on the screen. The char is the character
            the user wants printed to the screen
            Return Type: void 
       */
       void plot(int,int,char);
       
       /*
            Name: setColor
            Description: Determines which color the plotter is going to print
            Arguments: an ink; an enumerated data type that carries information 
            regaurding the color of a pixel.
            Return Type: void
       */
       void setColor(ink);
};


#endif /*PLOTTER_H_*/
