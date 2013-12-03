/******************************************************************************
Author:         Jonathan McElroy
Filename:       menu.cpp
Description:    Implements the menu system and starts the game
Date Modified:  December 2, 2013
******************************************************************************/
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

#include "constants.h"
#include "menu.h"

/*
Constructor
*/
Menu::Menu()
{

    //the options at the beginning of the game
    options[0] = Enigma_char;
    options[1] = Enigma_string;
    options[2] = Exit;
    numOfOptions = 3;
    //start at the enigma_char option
    myStateNum = 0;

    //sets the image to the menu file
    ifstream imageFile("Menu.txt");
    //sets the image colors
    ifstream imageColorFile("MenuColor.txt");
    image.setX(0);
    image.setY(0);
    image.setImage(imageFile, imageColorFile);
    image.draw();

    //sets the selection bar
    ifstream selectedFile("Selected.txt");
    selected.setX(SCREENWIDTH/2);
    selected.setY(SCREENHEIGHT/2-6);
    selected.setImage(selectedFile, white, center);
    selected.draw();

	//sets the second selection bar
	ifstream selected2File("KeySelect.txt");
	second_selected.setX(15);
	second_selected.setY(6);
	second_selected.setImage(selected2File, red, center);

	// the word we are encrypting
	word = "";
	wordImage.setImage(word, cyan, midLeft);
	wordImage.setX(2);
	wordImage.setY(SCREENHEIGHT/2 + 13);

	encryptWordImage.setImage("", red, midLeft);
	encryptWordImage.setX(2);
	encryptWordImage.setY(SCREENHEIGHT/2 + 19	 );

	leftRImage.setImage(encryption.getSetting3(), white, center);
	leftRImage.setX(129);
	leftRImage.setY(8);
	midRImage.setImage(encryption.getSetting2(), white, center);
	midRImage.setX(139);
	midRImage.setY(8);
	rightRImage.setImage(encryption.getSetting1(), white, center);
	rightRImage.setX(149);
	rightRImage.setY(8);

	ifstream selectedRotor("SelectRotor.txt");
	selectRotor.setX(129);
	selectRotor.setY(8);
	selectRotor.setImage(selectedRotor, yellow, center);

	currSelectRotor = 0;

	firstPlugChar = secondPlugChar = "";
	plugChars.setX(130);
	plugChars.setY(19);
	plugChars.setImage("", white);
}

void Menu::backspace()
{
	States myState = options[myStateNum];
	if (myState == Enigma_string_back)
	{
		selected.unDraw();
		encryptWordImage.unDraw();

		if (word.length() > 0) {
			wordImage.unDraw();
			word.resize(word.length()-1);
			wordImage.setImage(word, cyan, midLeft);
			wordImage.draw();
		}
	}
	if (myState == Enigma_char_plug_back || myState == Enigma_string_plug_back) {
		if(firstPlugChar.length() == secondPlugChar.length()) {
			if (firstPlugChar.length()) {
				plugChars.unDraw();
				encryption.unsetPlugboard(firstPlugChar[firstPlugChar.length()-1], secondPlugChar[secondPlugChar.length()-1]);
				firstPlugChar.resize(firstPlugChar.length()-1);
				secondPlugChar.resize(secondPlugChar.length()-1);
				string temp = "";
				for(int i=0; i<secondPlugChar.length(); i++) {
					temp += firstPlugChar[i];
					temp += " - ";
					temp += secondPlugChar[i];
					temp += "\n";
				}
				plugChars.setImage(temp, white);
				plugChars.draw();
			}
		} else {
			plugChars.unDraw();
			firstPlugChar.resize(firstPlugChar.length()-1);
			string temp = "";
			for(int i=0; i<secondPlugChar.length(); i++) {
				temp += firstPlugChar[i];
				temp += " - ";
				temp += secondPlugChar[i];
				temp += "\n";
			}
			plugChars.setImage(temp, white);
			plugChars.draw();
		}
	}
}

void Menu::tab() {
	States myState = options[myStateNum];
	if(myState == Enigma_char_back) {
		options[0] = Enigma_char_back;
		options[1] = Enigma_char_plug_back;
        numOfOptions = 1;
        myStateNum = 1;

		selected.unDraw();
		second_selected.unDraw();

		ifstream selectFile("PlugSelect.txt");
		selected.setImage(selectFile, green, center);
		selected.setX(134);
		selected.setY(24);
		selected.draw();
	}
	else if(myState == Enigma_char_plug_back) {
		options[0] = Enigma_char_back;
		options[1] = Enigma_char_plug_back;
        numOfOptions = 1;
        myStateNum = 0;

		selected.unDraw();
		second_selected.unDraw();
		if(firstPlugChar.length() == secondPlugChar.length()) {
			plugChars.unDraw();
			firstPlugChar.resize(firstPlugChar.length()-1);
			string temp = "";
			for(int i=0; i<secondPlugChar.length(); i++) {
				temp += firstPlugChar[i];
				temp += " - ";
				temp += secondPlugChar[i];
				temp += "\n";
			}
			plugChars.setImage(temp, white);
			plugChars.draw();
		}

		ifstream selectFile("KeySelect.txt");
        selected.setX(15);
        selected.setY(6);
        selected.setImage(selectFile, yellow, center);

	}
	else if(myState == Enigma_string_back) {
		options[0] = Enigma_string_back;
		options[1] = Enigma_string_plug_back;
        numOfOptions = 1;
        myStateNum = 1;

		selected.unDraw();
		second_selected.unDraw();

		ifstream selectFile("PlugSelect.txt");
		selected.setImage(selectFile, green, center);
		selected.setX(134);
		selected.setY(24);
		selected.draw();
	}
	else if(myState == Enigma_string_plug_back) {
		options[0] = Enigma_string_back;
		options[1] = Enigma_string_plug_back;
        numOfOptions = 1;
        myStateNum = 0;

		selected.unDraw();
		second_selected.unDraw();

		ifstream selectFile("KeySelect.txt");
        selected.setX(15);
        selected.setY(6);
        selected.setImage(selectFile, yellow, center);
	}
}

//called if enter is pressed
//if we exit, return true
int Menu::enter()
{
    bool exiting = false;
    States myState = options[myStateNum];
    //if we are on the char option
    if(myState == Enigma_char)
    {
        //make the only option to return to the menu
        options[0] = Enigma_char_back;
		options[1] = Enigma_char_plug_back;
        numOfOptions = 1;
        myStateNum = 0;

		selected.unDraw();
		image.unDraw();

        //hide the selection bar
        ifstream selectFile("KeySelect.txt");
        selected.setX(15);
        selected.setY(6);
        selected.setImage(selectFile, yellow, center);

        //hide the menu images
        ifstream stringFile("ClassicBoard.txt");
        image.setX(0);
        image.setY(0);
        image.setImage(stringFile, white);
        image.draw();

		leftRImage.setImage(encryption.getSetting3(), white, center);
		leftRImage.draw();
		midRImage.setImage(encryption.getSetting2(), white, center);
		midRImage.draw();
		rightRImage.setImage(encryption.getSetting1(), white, center);
		rightRImage.draw();
		selectRotor.draw();
    }
    //if we are on the Instructions option
    else if(myState == Enigma_string)
    {
		options[0] = Enigma_string_back;
		options[1] = Enigma_string_plug_back;
        numOfOptions = 1;
        myStateNum = 0;

		selected.unDraw();
		image.unDraw();

		//hide the selection bar
		ifstream selectFile("KeySelect.txt");
        selected.setX(15);
        selected.setY(6);
        selected.setImage(selectFile, yellow, center);

        //get and draw the instructions file
        ifstream stringFile("StringBoard.txt");
        image.setX(0);
        image.setY(0);
        image.setImage(stringFile, white);
        image.draw();

		leftRImage.setImage(encryption.getSetting3(), white, center);
		leftRImage.draw();
		midRImage.setImage(encryption.getSetting2(), white, center);
		midRImage.draw();
		rightRImage.setImage(encryption.getSetting1(), white, center);
		rightRImage.draw();
		selectRotor.draw();
	}
    else if(myState == Enigma_string_back || myState == Enigma_string_plug_back)
    {
		encryption.setSetting3(encryption.getSetting3().c_str()[0]);
		encryption.setSetting2(encryption.getSetting2().c_str()[0]);
		encryption.setSetting1(encryption.getSetting1().c_str()[0]);
		encryptWordImage.setImage(encryption.encryptString(word), red, midLeft);
		encryptWordImage.draw();
		leftRImage.setImage(encryption.getSetting3(), white, center);
		leftRImage.draw();
		midRImage.setImage(encryption.getSetting2(), white, center);
		midRImage.draw();
		rightRImage.setImage(encryption.getSetting1(), white, center);
		rightRImage.draw();
    }
    //if we are returning from viewing the credits
    //if we are on the Exit option
    else if(myState == Exit)
    {
        //quit the game
        exiting = true;
    }
    return exiting;
}

//called if escape is pressed
void Menu::escape()
{
    States myState = options[myStateNum];
    if(myState == Enigma_char_back || myState == Enigma_char_plug_back)
    {
        //reset the main options, starting on enigma_char
        options[0] = Enigma_char;
        options[1] = Enigma_string;
        options[2] = Exit;
        numOfOptions = 3;
        myStateNum = 0;

		selected.unDraw();
		second_selected.unDraw();
		image.unDraw();
		//remove the strings and rotors
		wordImage.unDraw();
		encryptWordImage.unDraw();
		leftRImage.unDraw();
		midRImage.unDraw();
		rightRImage.unDraw();
		selectRotor.unDraw();

		// reset the word to encrypt
		word = "";

        //get and draw the menu file
        ifstream imageFile("Menu.txt");
        ifstream imageColorFile("MenuColor.txt");
        image.setX(0);
        image.setY(0);
        image.setImage(imageFile, imageColorFile);
        image.draw();

        //move the selection bar
        ifstream selectFile("Selected.txt");
        selected.setImage(selectFile, white, center);
        selected.move(SCREENWIDTH/2, SCREENHEIGHT/2-6);

		encryption.setSetting3(encryption.getSetting3().c_str()[0]);
		encryption.setSetting2(encryption.getSetting2().c_str()[0]);
		encryption.setSetting1(encryption.getSetting1().c_str()[0]);
    }
	if(myState == Enigma_string_back || myState == Enigma_string_plug_back)
    {
        //reset the main options, starting on play
        options[0] = Enigma_char;
        options[1] = Enigma_string;
        options[2] = Exit;
        numOfOptions = 3;
        myStateNum = 1;

		selected.unDraw();
		image.unDraw();

		word = "";
		wordImage.unDraw();
		encryptWordImage.unDraw();
		leftRImage.unDraw();
		midRImage.unDraw();
		rightRImage.unDraw();
		selectRotor.unDraw();

        //get and draw the menu file
        ifstream imageFile("Menu.txt");
        ifstream imageColorFile("MenuColor.txt");
        image.setX(0);
        image.setY(0);
        image.setImage(imageFile, imageColorFile);
        image.draw();

        //move the selection bar
        ifstream selectFile("Selected.txt");
        selected.setImage(selectFile, white, center);
        selected.move(SCREENWIDTH/2, SCREENHEIGHT/2-3);

		encryption.setSetting3(encryption.getSetting3().c_str()[0]);
		encryption.setSetting2(encryption.getSetting2().c_str()[0]);
		encryption.setSetting1(encryption.getSetting1().c_str()[0]);
    }
}

void Menu::keyPushed(char key)
{
    States myState = options[myStateNum];
	if (myState == Enigma_char_back) {
		ifstream selectFile("KeySelect.txt");
        selected.unDraw();
		second_selected.unDraw();

        selected.setImage(selectFile, green, center);
		selectFile.close();
		switch(key) {
		case 'Q': case 'q': selected.setX(15); selected.setY(6); break;
        case 'W': case 'w': selected.setX(25); selected.setY(6); break;
        case 'E': case 'e': selected.setX(35); selected.setY(6); break;
        case 'R': case 'r': selected.setX(45); selected.setY(6); break;
        case 'T': case 't': selected.setX(55); selected.setY(6); break;
        case 'Y': case 'y': selected.setX(65); selected.setY(6); break;
        case 'U': case 'u': selected.setX(75); selected.setY(6); break;
        case 'I': case 'i': selected.setX(85); selected.setY(6); break;
        case 'O': case 'o': selected.setX(95); selected.setY(6); break;
        case 'P': case 'p': selected.setX(105); selected.setY(6); break;
        case 'A': case 'a': selected.setX(19); selected.setY(14); break;
        case 'S': case 's': selected.setX(29); selected.setY(14); break;
        case 'D': case 'd': selected.setX(39); selected.setY(14); break;
        case 'F': case 'f': selected.setX(49); selected.setY(14); break;
        case 'G': case 'g': selected.setX(59); selected.setY(14); break;
        case 'H': case 'h': selected.setX(69); selected.setY(14); break;
        case 'J': case 'j': selected.setX(79); selected.setY(14); break;
        case 'K': case 'k': selected.setX(89); selected.setY(14); break;
        case 'L': case 'l': selected.setX(99); selected.setY(14); break;
        case 'Z': case 'z': selected.setX(23); selected.setY(22); break;
        case 'X': case 'x': selected.setX(33); selected.setY(22); break;
        case 'C': case 'c': selected.setX(43); selected.setY(22); break;
        case 'V': case 'v': selected.setX(53); selected.setY(22); break;
        case 'B': case 'b': selected.setX(63); selected.setY(22); break;
        case 'N': case 'n': selected.setX(73); selected.setY(22); break;
        case 'M': case 'm': selected.setX(83); selected.setY(22); break;
		}
		selected.draw();
		char new_key = encryption.encryptString(string(1, key))[0];
		leftRImage.setImage(encryption.getSetting3(), white, center);
		leftRImage.draw();
		midRImage.setImage(encryption.getSetting2(), white, center);
		midRImage.draw();
		rightRImage.setImage(encryption.getSetting1(), white, center);
		rightRImage.draw();
		switch(new_key) {
		case 'Q': case 'q': second_selected.setX(15); second_selected.setY(6); break;
        case 'W': case 'w': second_selected.setX(25); second_selected.setY(6); break;
        case 'E': case 'e': second_selected.setX(35); second_selected.setY(6); break;
        case 'R': case 'r': second_selected.setX(45); second_selected.setY(6); break;
        case 'T': case 't': second_selected.setX(55); second_selected.setY(6); break;
        case 'Y': case 'y': second_selected.setX(65); second_selected.setY(6); break;
        case 'U': case 'u': second_selected.setX(75); second_selected.setY(6); break;
        case 'I': case 'i': second_selected.setX(85); second_selected.setY(6); break;
        case 'O': case 'o': second_selected.setX(95); second_selected.setY(6); break;
        case 'P': case 'p': second_selected.setX(105); second_selected.setY(6); break;
        case 'A': case 'a': second_selected.setX(19); second_selected.setY(14); break;
        case 'S': case 's': second_selected.setX(29); second_selected.setY(14); break;
        case 'D': case 'd': second_selected.setX(39); second_selected.setY(14); break;
        case 'F': case 'f': second_selected.setX(49); second_selected.setY(14); break;
        case 'G': case 'g': second_selected.setX(59); second_selected.setY(14); break;
        case 'H': case 'h': second_selected.setX(69); second_selected.setY(14); break;
        case 'J': case 'j': second_selected.setX(79); second_selected.setY(14); break;
        case 'K': case 'k': second_selected.setX(89); second_selected.setY(14); break;
        case 'L': case 'l': second_selected.setX(99); second_selected.setY(14); break;
        case 'Z': case 'z': second_selected.setX(23); second_selected.setY(22); break;
        case 'X': case 'x': second_selected.setX(33); second_selected.setY(22); break;
        case 'C': case 'c': second_selected.setX(43); second_selected.setY(22); break;
        case 'V': case 'v': second_selected.setX(53); second_selected.setY(22); break;
        case 'B': case 'b': second_selected.setX(63); second_selected.setY(22); break;
        case 'N': case 'n': second_selected.setX(73); second_selected.setY(22); break;
        case 'M': case 'm': second_selected.setX(83); second_selected.setY(22); break;
		}
		second_selected.draw();
	}
	else if (myState == Enigma_char_plug_back) {
		asmToLower(&key);
		if(firstPlugChar.length() == secondPlugChar.length()) {
			if (firstPlugChar.length() < 10) {
				firstPlugChar += key;
				string temp = "";
				for(int i=0; i<secondPlugChar.length(); i++) {
					temp += firstPlugChar[i];
					temp += " - ";
					temp += secondPlugChar[i];
					temp += "\n";
				}
				temp += firstPlugChar[firstPlugChar.length()-1];
				temp += " : ";
				plugChars.setImage(temp, white);
				plugChars.draw();
			}
		} else {
			if (firstPlugChar[firstPlugChar.length()-1] != key) {
				plugChars.unDraw();

				int changed = encryption.setPlugboard(firstPlugChar[firstPlugChar.length()-1], key);
				char char2 = changed & 0xFF;
				char char1 = (changed >> 8) & 0xFF;
				
				for(int i=0; i<secondPlugChar.length(); i++) {
					if (firstPlugChar[i] == char1 || secondPlugChar[i] == char1) {
						firstPlugChar.erase(i, 1);
						secondPlugChar.erase(i, 1);
						break;
					}
				}
				for(int i=0; i<secondPlugChar.length(); i++) {
					if (firstPlugChar[i] == char2 || secondPlugChar[i] == char2) {
						firstPlugChar.erase(i, 1);
						secondPlugChar.erase(i, 1);
						break;
					}
				}
				secondPlugChar += key;
				string temp = "";
				for(int i=0; i<secondPlugChar.length(); i++) {
					temp += firstPlugChar[i];
					temp += " - ";
					temp += secondPlugChar[i];
					temp += "\n";
				}
				plugChars.setImage(temp, white);
				plugChars.draw();
			}
		}
	}
    else if (myState == Enigma_string_back)
    {
		selected.unDraw();
		encryptWordImage.unDraw();

		ifstream selectFile("KeySelect.txt");
        selected.setImage(selectFile, green, center);
		selectFile.close();
        switch(key) {
        case 'Q': case 'q': selected.setX(15); selected.setY(6); break;
        case 'W': case 'w': selected.setX(25); selected.setY(6); break;
        case 'E': case 'e': selected.setX(35); selected.setY(6); break;
        case 'R': case 'r': selected.setX(45); selected.setY(6); break;
        case 'T': case 't': selected.setX(55); selected.setY(6); break;
        case 'Y': case 'y': selected.setX(65); selected.setY(6); break;
        case 'U': case 'u': selected.setX(75); selected.setY(6); break;
        case 'I': case 'i': selected.setX(85); selected.setY(6); break;
        case 'O': case 'o': selected.setX(95); selected.setY(6); break;
        case 'P': case 'p': selected.setX(105); selected.setY(6); break;
        case 'A': case 'a': selected.setX(19); selected.setY(14); break;
        case 'S': case 's': selected.setX(29); selected.setY(14); break;
        case 'D': case 'd': selected.setX(39); selected.setY(14); break;
        case 'F': case 'f': selected.setX(49); selected.setY(14); break;
        case 'G': case 'g': selected.setX(59); selected.setY(14); break;
        case 'H': case 'h': selected.setX(69); selected.setY(14); break;
        case 'J': case 'j': selected.setX(79); selected.setY(14); break;
        case 'K': case 'k': selected.setX(89); selected.setY(14); break;
        case 'L': case 'l': selected.setX(99); selected.setY(14); break;
        case 'Z': case 'z': selected.setX(23); selected.setY(22); break;
        case 'X': case 'x': selected.setX(33); selected.setY(22); break;
        case 'C': case 'c': selected.setX(43); selected.setY(22); break;
        case 'V': case 'v': selected.setX(53); selected.setY(22); break;
        case 'B': case 'b': selected.setX(63); selected.setY(22); break;
        case 'N': case 'n': selected.setX(73); selected.setY(22); break;
        case 'M': case 'm': selected.setX(83); selected.setY(22); break;
        }
		selected.draw();

		word += key;
		wordImage.setImage(word, cyan, midLeft);
		wordImage.draw();
    }
	else if (myState == Enigma_string_plug_back)
    {
		asmToLower(&key);
		if(firstPlugChar.length() == secondPlugChar.length()) {
			if (firstPlugChar.length() < 10) {
				firstPlugChar += key;
				string temp = "";
				for(int i=0; i<secondPlugChar.length(); i++) {
					temp += firstPlugChar[i];
					temp += " - ";
					temp += secondPlugChar[i];
					temp += "\n";
				}
				temp += firstPlugChar[firstPlugChar.length()-1];
				temp += " : ";
				plugChars.setImage(temp, white);
				plugChars.draw();
			}
		} else {
			if (firstPlugChar[firstPlugChar.length()-1] != key) {
				plugChars.unDraw();
				int changed = encryption.setPlugboard(firstPlugChar[firstPlugChar.length()-1], key);
				char char2 = changed & 0xFF;
				char char1 = (changed >> 8) & 0xFF;
				
				for(int i=0; i<secondPlugChar.length(); i++) {
					if (firstPlugChar[i] == char1 || secondPlugChar[i] == char1) {
						firstPlugChar.erase(i, 1);
						secondPlugChar.erase(i, 1);
						break;
					}
				}
				for(int i=0; i<secondPlugChar.length(); i++) {
					if (firstPlugChar[i] == char2 || secondPlugChar[i] == char2) {
						firstPlugChar.erase(i, 1);
						secondPlugChar.erase(i, 1);
						break;
					}
				}
				secondPlugChar += key;
				string temp = "";
				for(int i=0; i<secondPlugChar.length(); i++) {
					temp += firstPlugChar[i];
					temp += " - ";
					temp += secondPlugChar[i];
					temp += "\n";
				}
				plugChars.setImage(temp, white);
				plugChars.draw();
			}
		}
	}
}

void Menu::space() {
	States myState = options[myStateNum];
	if (myState == Enigma_char_back || myState == Enigma_string_back) {
		second_selected.unDraw();
		selected.unDraw();
		wordImage.unDraw();

		ifstream selectFile("SpaceSelect.txt");
        selected.setImage(selectFile, green, center);
		selected.setX(54);
		selected.setY(30);
		selected.draw();
		selectFile.close();

		word += ' ';
		wordImage.setImage(word, cyan, midLeft);
		wordImage.draw();
	}
}

//called if up is pressed
void Menu::moveUp()
{
    States myState = options[myStateNum];
	if(myState == Enigma_char_back || myState == Enigma_string_back || myState == Enigma_char_plug_back || myState == Enigma_string_plug_back) {
		switch(currSelectRotor) {
		case 0:
			{
				if (encryption.getSetting3() == "Z")
					encryption.setSetting3('A');
				else
					encryption.setSetting3(encryption.getSetting3().c_str()[0]+1);
				leftRImage.setImage(encryption.getSetting3(), white, center);
				leftRImage.draw();
				break;
			}
		case 1:
			{
				if (encryption.getSetting2() == "Z")
					encryption.setSetting2('A');
				else
					encryption.setSetting2(encryption.getSetting2().c_str()[0]+1);
				midRImage.setImage(encryption.getSetting2(), white, center);
				midRImage.draw();
				break;
			}
		case 2:
			{
				if (encryption.getSetting1() == "Z")
					encryption.setSetting1('A');
				else
					encryption.setSetting1(encryption.getSetting1().c_str()[0]+1);
				rightRImage.setImage(encryption.getSetting1(), white, center);
				rightRImage.draw();
				break;
			}
		}
	}
    //if we are in the menu and not at the top
	else if((myState == Enigma_char || myState == Enigma_string || myState == Exit) && myStateNum>0)
    {
        //move up
        myStateNum--;
        selected.move(selected.getX(),selected.getY()-3);
    }
}

//called if left is pressed
void Menu::moveLeft()
{
    States myState = options[myStateNum];
    if(myState == Enigma_char_back || myState == Enigma_string_back || myState == Enigma_char_plug_back || myState == Enigma_string_plug_back) {
		currSelectRotor = (currSelectRotor+2)%3;
		selectRotor.unDraw();
		selectRotor.setX(129+currSelectRotor*10);
		selectRotor.draw();
	}
}

//called if right is pressed
void Menu::moveRight()
{
    States myState = options[myStateNum];
    if(myState == Enigma_char_back || myState == Enigma_string_back || myState == Enigma_char_plug_back || myState == Enigma_string_plug_back) {
		currSelectRotor = (currSelectRotor+1)%3;
		selectRotor.unDraw();
		selectRotor.setX(129+currSelectRotor*10);
		selectRotor.draw();
	}
}

//called if down is pressed
void Menu::moveDown()
{
    States myState = options[myStateNum];
	if(myState == Enigma_char_back || myState == Enigma_string_back || myState == Enigma_char_plug_back || myState == Enigma_string_plug_back) {
		switch(currSelectRotor) {
		case 0:
			{
				if (encryption.getSetting3() == "A")
					encryption.setSetting3('Z');
				else
					encryption.setSetting3(encryption.getSetting3().c_str()[0]-1);
				leftRImage.setImage(encryption.getSetting3(), white, center);
				leftRImage.draw();
				break;
			}
		case 1:
			{
				if (encryption.getSetting2() == "A")
					encryption.setSetting2('Z');
				else
					encryption.setSetting2(encryption.getSetting2().c_str()[0]-1);
				midRImage.setImage(encryption.getSetting2(), white, center);
				midRImage.draw();
				break;
			}
		case 2:
			{
				if (encryption.getSetting1() == "A")
					encryption.setSetting1('Z');
				else
					encryption.setSetting1(encryption.getSetting1().c_str()[0]-1);
				rightRImage.setImage(encryption.getSetting1(), white, center);
				rightRImage.draw();
				break;
			}
		}
	}
    //if we are in the menu and not at the bottom
    else if((myState == Enigma_char || myState == Enigma_string || myState == Exit) && myStateNum<numOfOptions-1)
    {
        //move down
        myStateNum++;
        selected.move(selected.getX(),selected.getY()+3);
    }
}
