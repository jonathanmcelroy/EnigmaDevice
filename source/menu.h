/*
	Authors: Jonathan McElroy, Aaron Salinas, Elise Brown
	FileName: menu.h
	Description: the header file for the menu screen
*/
#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "sprite.h"
#include "Encrypt.h"
//#include "animation.h"
//#include "score.h"
//#include "cannon.h"
//#include "city.h"

//the states that the menu can be in
enum States
{
    Enigma_char,
	Enigma_char_back,
	Enigma_char_plug_back,
    Enigma_string,
	Enigma_string_back,
	Enigma_string_plug_back,
    Exit
};

//this class impiments the menu system and starts the game
class Menu
{
    private:
		Encrypt encryption;

        //the list of options we have now
        States options[3];
        int numOfOptions;
        int myStateNum;

        //the menu image
        Sprite image;
        //the selection bar image
        Sprite selected;
	//the secondary selection bar image
	Sprite second_selected;
	//word to encrypt
	string word;
	Sprite wordImage;
	//encrypted word
	Sprite encryptWordImage;

	Sprite leftRImage;
	Sprite midRImage;
	Sprite rightRImage;

	int currSelectRotor;
	Sprite selectRotor;

	string firstPlugChar, secondPlugChar, plugString;
	Sprite plugChars;

    public:
        Menu();
		void backspace();
		void tab();
        int enter();
        void escape();
        void keyPushed(char key);

        //called when the relative key is pressed
        //up, w
        void moveUp();
        //left, a
        void moveLeft();
        //right, d
        void moveRight();
        //down, s
        void moveDown();
        //space
        void space();
};

#endif // MENU_H_INCLUDED
