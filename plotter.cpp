//Plotter.cpp was provided by CSI 1430 
//Used by Jonathan McElroy, Aaron Salinas, Elise Brown
//this is needed to make the screen biggers

#define _WIN32_WINNT 0x0601
#include <iostream>
using namespace std;

#include "constants.h"
#include "plotter.h"

/*
	Description:  This is the plotter default constructor
	it sets the member variables of coordScreen to zero 
	a coorScreen represents the coordinates on the terminal

	The default constructor sets the dimensions of the screen
	and makes the cursor invisible
*/
Plotter::Plotter()
{
      coordScreen.X = 0;
      coordScreen.Y = 0;

      hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
      SetConsoleTextAttribute(hConsoleOutput, green);

      //this makes the screen bigger
      COORD c = {SCREENWIDTH,SCREENHEIGHT};
      SetConsoleScreenBufferSize(hConsoleOutput, c);
      SMALL_RECT rect = {0, 0, SCREENWIDTH-1, SCREENHEIGHT-1};
      SetConsoleWindowInfo(hConsoleOutput, true, &rect);

      //makes the cursor invisible so that the cursor doesn't
	  //blink
      CONSOLE_CURSOR_INFO cursor = {1,false};
      SetConsoleCursorInfo(hConsoleOutput, &cursor);
}


/*
	Description: This allows the user to set the coordinates for
	the cursor. 

*/
void Plotter::move(int x, int y)
{
      coordScreen.X = x;
      coordScreen.Y = y;
      //SetConsoleTextAttribute(hConsoleOutput, c);
      SetConsoleCursorPosition( hConsoleOutput, coordScreen );
}

/*
	Description: This function allows the user to set the coordinates for the
	cursor, and then takes the character c and uses the cursor to print the char
	at the specified location.
*/
void Plotter::plot(int x, int y, char c)
{
      coordScreen.X = x;
      coordScreen.Y = y;
      //SetConsoleTextAttribute(hConsoleOutput, c);
      SetConsoleCursorPosition( hConsoleOutput, coordScreen );
      cout  << c;
      cout.flush();
}

/*
	Description: Allows the user to set the color of the Plotter output
	with an ink object
*/
void Plotter::setColor(ink c)
{
	SetConsoleTextAttribute(hConsoleOutput, c);
}

/*
	Description: This is a wrapper function that calls the cls method
	from the plotter class
*/
void Plotter::clear()
{
	cls( hConsoleOutput );
}




/*
	Description: This function clears the plotter's console reverting the
	plotter to show a blank screen
*/
void Plotter::cls( HANDLE hConsole )
{
 COORD coordScreen = { 0, 0 };    // here's where we'll home the cursor

 DWORD cCharsWritten;
 CONSOLE_SCREEN_BUFFER_INFO csbi; // to get buffer info
 DWORD dwConSize;                 // number of character cells in the current buffer

 // get the number of character cells in the current buffer

 GetConsoleScreenBufferInfo( hConsole, &csbi );
 dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

 // fill the entire screen with blanks

 FillConsoleOutputCharacter( hConsole, (TCHAR) ' ', dwConSize, coordScreen, &cCharsWritten );

 // get the current text attribute

 GetConsoleScreenBufferInfo( hConsole, &csbi );

 // now set the buffer's attributes accordingly

 FillConsoleOutputAttribute( hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten );

 // put the cursor at (0, 0)

 SetConsoleCursorPosition( hConsole, coordScreen );

 return;
}
