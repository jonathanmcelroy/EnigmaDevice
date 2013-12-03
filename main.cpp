/*
	Authors: Jonathan McElroy, Aaron Salinas, Elise Brown
	FileName: main.cpp
	Description: controls which keys light up on the Enigma
	Keyboard, also gives instruction on what to do if special
	keys are pressed (i.e. tab and backspace)
*/
#include <iostream>
#include <fstream>

#include "plotter.h"
#include "menu.h"

using namespace std;

int main()
{

    //these braces makes everything go out of scope at the end, forcing the sprites to undraw
    {
        //creates the menu
        Menu menu;

        //the keyboard input
        int keyPressed = 0;
        //continue while not quiting
        bool quit = false;
        while(!quit)
        {
            //if a key is hit
            if(_kbhit())
            {
                //get the key hit
                keyPressed = _getch();
				//if backspace is pressed
				if (keyPressed == 8) menu.backspace();
				//if tab is pressed
				if (keyPressed == 9) menu.tab();
                //if enter is pressed
                if (keyPressed == 13) quit = menu.enter();
                //if escape is pressed
                else if (keyPressed == 27) menu.escape();
                //if a char is pressed
                else if (isalpha(keyPressed)) menu.keyPushed(keyPressed);
				//if space is pressed
				else if (keyPressed == ' ') menu.space();
				//if a special key is pressed, two keystrokes are placed in the buffer
				else if (keyPressed == 224) {
					keyPressed = _getch();
                    switch(keyPressed)
                    {
                    //if up was pressed
                    case 72:
                        menu.moveUp();
                        break;
                    //if left was pressed
                    case 75:
                        menu.moveLeft();
                        break;
                    //if right was pressed
                    case 77:
                        menu.moveRight();
                        break;
                    //if down was pressed
                    case 80:
                        menu.moveDown();
                        break;
                    }
				}
            }
        }
    }
    //put the ending message at the beginning
    Plotter p;
    p.setColor(white);
    p.move(0,0);

    return 0;
}
