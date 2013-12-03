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
Default Constructor

Defines all the values when the application starts
*/
Menu::Menu() {

    //the menu options at the beginning of the game
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

    //sets the secondary selection bar
    ifstream selected2File("KeySelect.txt");
    second_selected.setX(15);
    second_selected.setY(6);
    second_selected.setImage(selected2File, red, center);

    // the word we are encrypting
    word = "";
    wordImage.setImage(word, cyan, midLeft);
    wordImage.setX(2);
    wordImage.setY(SCREENHEIGHT/2 + 13);

    // the word we have encrypted
    encryptWordImage.setImage("", red, midLeft);
    encryptWordImage.setX(2);
    encryptWordImage.setY(SCREENHEIGHT/2 + 19    );

    // the rotors
    leftRImage.setImage(encryption.getSetting3(), white, center);
    leftRImage.setX(129);
    leftRImage.setY(8);
    midRImage.setImage(encryption.getSetting2(), white, center);
    midRImage.setX(139);
    midRImage.setY(8);
    rightRImage.setImage(encryption.getSetting1(), white, center);
    rightRImage.setX(149);
    rightRImage.setY(8);

    // the rotor selected
    currSelectRotor = 0;
    ifstream selectedRotor("SelectRotor.txt");
    selectRotor.setX(129);
    selectRotor.setY(8);
    selectRotor.setImage(selectedRotor, yellow, center);

    // the plugboard settings
    firstPlugChar = secondPlugChar = plugString = "";
    plugChars.setX(130);
    plugChars.setY(19);
    plugChars.setImage(plugString, white);
}

/*
Called when the backspace key is pressed

If the application is in enigma string mode, then the last character entered to
the encryption string is removed. Because the rotors are not rotated until the
string is encrypted, the rotors do not need to be changed.
If the application is in either of the plugboard editing modes, then the last
entered setting will be removed.
*/
void Menu::backspace() {
    // get the current state
    States myState = options[myStateNum];
    // if we are in the Enigma string mode
    if (myState == Enigma_string_back)
    {
        // Erase the sprites of the selection bar around the key and the
        // encrypted word.
        selected.unDraw();
        encryptWordImage.unDraw();

        // if the word has characters in it, remove the last character.
        if (word.length() > 0) {
            wordImage.unDraw();
            word.resize(word.length()-1);
            wordImage.setImage(word, cyan, midLeft);
            wordImage.draw();
        }
    }
    // if we are in the in a plugboard editing mode
    if (myState == Enigma_char_plug_back || myState == Enigma_string_plug_back) {
        // if we only have whole entered settings, remove the last one
        if(firstPlugChar.length() == secondPlugChar.length()) {
            // if there are at least one setting, remove the last
            if (firstPlugChar.length()) {
                // Erase the plugboard setting sprite
                plugChars.unDraw();
                // unset the plugboard setting
                encryption.unsetPlugboard(
                        firstPlugChar[firstPlugChar.length()-1],
                        secondPlugChar[secondPlugChar.length()-1]);
                // remove the last setting
                firstPlugChar.resize(firstPlugChar.length()-1);
                secondPlugChar.resize(secondPlugChar.length()-1);
                plugString = "";
                for(int i=0; i<secondPlugChar.length(); i++) {
                    plugString += firstPlugChar[i];
                    plugString += " - ";
                    plugString += secondPlugChar[i];
                    plugString += "\n";
                }
                plugChars.setImage(plugString, white);
                plugChars.draw();
            }
        }
        // if we have a half entered setting, remove that
        else {
            // Erase the plugboard setting sprite
            plugChars.unDraw();
            // remove the half setting
            firstPlugChar.resize(firstPlugChar.length()-1);
            plugString = "";
            for(int i=0; i<secondPlugChar.length(); i++) {
                plugString += firstPlugChar[i];
                plugString += " - ";
                plugString += secondPlugChar[i];
                plugString += "\n";
            }
            plugChars.setImage(plugString, white);
            plugChars.draw();
        }
    }
}

/*
Called when the tab key is pressed

If the application is in either Enigma char mode and Enigma string mode, switch
between key editing mode and plugboard editing mode.
*/
void Menu::tab() {
    // get the current mode
    States myState = options[myStateNum];
    // if we are in enigma char mode, adding keys
    if(myState == Enigma_char_back) {
        // set the current settings
        options[0] = Enigma_char_back;
        options[1] = Enigma_char_plug_back;
        numOfOptions = 1;
        myStateNum = 1;

        // erase the selection sprite and secondary selection sprite
        selected.unDraw();
        second_selected.unDraw();

        // draw the plugboard selection sprite
        ifstream selectFile("PlugSelect.txt");
        selected.setImage(selectFile, green, center);
        selected.setX(134);
        selected.setY(31);
        selected.draw();
    }
    else if(myState == Enigma_char_plug_back) {
        // set the current settings
        options[0] = Enigma_char_back;
        options[1] = Enigma_char_plug_back;
        numOfOptions = 1;
        myStateNum = 0;

        // erase the selection sprite and secondary selection sprite
        selected.unDraw();
        second_selected.unDraw();
        // if the plugboard has an half entered setting, remove it
        if(firstPlugChar.length() != secondPlugChar.length()) {
            plugChars.unDraw();
            firstPlugChar.resize(firstPlugChar.length()-1);
            plugString = "";
            for(int i=0; i<secondPlugChar.length(); i++) {
                plugString += firstPlugChar[i];
                plugString += " - ";
                plugString += secondPlugChar[i];
                plugString += "\n";
            }
            plugChars.setImage(plugString, white);
            plugChars.draw();
        }

        // set the key selection sprite
        ifstream selectFile("KeySelect.txt");
        selected.setX(15);
        selected.setY(13);
        selected.setImage(selectFile, yellow, center);

    }
    else if(myState == Enigma_string_back) {
        // set the current settings
        options[0] = Enigma_string_back;
        options[1] = Enigma_string_plug_back;
        numOfOptions = 1;
        myStateNum = 1;

        // erase the selection sprite and secondary selection sprite
        selected.unDraw();

        // draw the plugboard selection sprite
        ifstream selectFile("PlugSelect.txt");
        selected.setImage(selectFile, green, center);
        selected.setX(134);
        selected.setY(24);
        selected.draw();
    }
    else if(myState == Enigma_string_plug_back) {
        // set the current settings
        options[0] = Enigma_string_back;
        options[1] = Enigma_string_plug_back;
        numOfOptions = 1;
        myStateNum = 0;

        // erase the selection sprite and secondary selection sprite
        selected.unDraw();
        // if the plugboard has an half entered setting, remove it
        if(firstPlugChar.length() != secondPlugChar.length()) {
            plugChars.unDraw();
            firstPlugChar.resize(firstPlugChar.length()-1);
            plugString = "";
            for(int i=0; i<secondPlugChar.length(); i++) {
                plugString += firstPlugChar[i];
                plugString += " - ";
                plugString += secondPlugChar[i];
                plugString += "\n";
            }
            plugChars.setImage(plugString, white);
            plugChars.draw();
        }

        // set the key selection sprite
        ifstream selectFile("KeySelect.txt");
        selected.setX(15);
        selected.setY(6);
        selected.setImage(selectFile, yellow, center);
    }
}

/*
Called when the enter key is pressed

If the application is in menu mode, enter the mode the selection bar is pointing
at. If the mode pointed to is "Exit", exit the program
If the application is in enigma string mode, encrypt the current encryption
string and display the result.
*/
int Menu::enter() {
    bool exiting = false;
    // get the current mode
    States myState = options[myStateNum];
    // if we are on the char option
    if(myState == Enigma_char) {
        // set the current settings
        options[0] = Enigma_char_back;
        options[1] = Enigma_char_plug_back;
        numOfOptions = 1;
        myStateNum = 0;

        // erase the selection bar and the background image
        selected.unDraw();
        image.unDraw();

        // move the selection bar
        ifstream selectFile("KeySelect.txt");
        selected.setX(15);
        selected.setY(13);
        selected.setImage(selectFile, yellow, center);

        // change and draw the background image
        ifstream stringFile("ClassicBoard.txt");
        image.setX(0);
        image.setY(0);
        image.setImage(stringFile, white);
        image.draw();

        // move and draw the rotors
        leftRImage.setImage(encryption.getSetting3(), white, center);
        leftRImage.setX(129);
        leftRImage.setY(15);
        leftRImage.draw();
        midRImage.setImage(encryption.getSetting2(), white, center);
        midRImage.setX(139);
        midRImage.setY(15);
        midRImage.draw();
        rightRImage.setImage(encryption.getSetting1(), white, center);
        rightRImage.setX(149);
        rightRImage.setY(15);
        rightRImage.draw();

        // move and draw the rotor selection
        selectRotor.setX(129);
        selectRotor.setY(15);
        selectRotor.draw();

        // move and draw the plugboard settings
        plugChars.setX(130);
        plugChars.setY(26);
        plugChars.draw();
    }
    // if we are on the string  option
    else if(myState == Enigma_string) {
        // set the current settings
        options[0] = Enigma_string_back;
        options[1] = Enigma_string_plug_back;
        numOfOptions = 1;
        myStateNum = 0;

        // erase the selection bar and the background image
        selected.unDraw();
        image.unDraw();

        // move the selection bar
        ifstream selectFile("KeySelect.txt");
        selected.setX(15);
        selected.setY(6);
        selected.setImage(selectFile, yellow, center);

        // change and draw the background image
        ifstream stringFile("StringBoard.txt");
        image.setX(0);
        image.setY(0);
        image.setImage(stringFile, white);
        image.draw();

        // move and draw the rotors
        leftRImage.setImage(encryption.getSetting3(), white, center);
        leftRImage.setX(129);
        leftRImage.setY(8);
        leftRImage.draw();
        midRImage.setImage(encryption.getSetting2(), white, center);
        midRImage.setX(139);
        midRImage.setY(8);
        midRImage.draw();
        rightRImage.setImage(encryption.getSetting1(), white, center);
        rightRImage.setX(149);
        rightRImage.setY(8);
        rightRImage.draw();

        // move and draw the rotor selection
        selectRotor.setX(129);
        selectRotor.setY(8);
        selectRotor.draw();

        // move and draw the plugboard settings
        plugChars.setX(130);
        plugChars.setY(19);
        plugChars.draw();
    }
    // if we are in the enigma string mode
    else if(myState == Enigma_string_back || myState == Enigma_string_plug_back) {
        // set the rotor settings to the encryption class
        encryption.setSetting3(encryption.getSetting3().c_str()[0]);
        encryption.setSetting2(encryption.getSetting2().c_str()[0]);
        encryption.setSetting1(encryption.getSetting1().c_str()[0]);
        // encrypt the string and set the image
        encryptWordImage.setImage(encryption.encryptString(word), red, midLeft);
        // draw the encrypted word
        encryptWordImage.draw();
        // update the rotors
        leftRImage.setImage(encryption.getSetting3(), white, center);
        leftRImage.draw();
        midRImage.setImage(encryption.getSetting2(), white, center);
        midRImage.draw();
        rightRImage.setImage(encryption.getSetting1(), white, center);
        rightRImage.draw();
    }
    // if we are on the Exit option
    else if(myState == Exit) {
        //quit the game
        exiting = true;
    }
    return exiting;
}

/*
Called when the escape key is pressed

If the application is in enigma mode, return to the main menu
*/
void Menu::escape() {
    // get the current setting
    States myState = options[myStateNum];
    // if we are in enigma char mode
    if(myState == Enigma_char_back || myState == Enigma_char_plug_back) {
        //reset the main options, starting on enigma_char
        options[0] = Enigma_char;
        options[1] = Enigma_string;
        options[2] = Exit;
        numOfOptions = 3;
        myStateNum = 0;

        // erase all the spites
        selected.unDraw();
        second_selected.unDraw();
        wordImage.unDraw();
        encryptWordImage.unDraw();
        leftRImage.unDraw();
        midRImage.unDraw();
        rightRImage.unDraw();
        selectRotor.unDraw();
        image.unDraw();

        // reset the word to encrypt
        word = "";

        // get and draw the menu file
        ifstream imageFile("Menu.txt");
        ifstream imageColorFile("MenuColor.txt");
        image.setX(0);
        image.setY(0);
        image.setImage(imageFile, imageColorFile);
        image.draw();

        // move and draw the selection bar
        ifstream selectFile("Selected.txt");
        selected.setImage(selectFile, white, center);
        selected.setX(SCREENWIDTH/2);
        selected.setY(SCREENHEIGHT/2-6);
        selected.draw();

        // set the current rotor settings
        encryption.setSetting3(encryption.getSetting3().c_str()[0]);
        encryption.setSetting2(encryption.getSetting2().c_str()[0]);
        encryption.setSetting1(encryption.getSetting1().c_str()[0]);
        currSelectRotor = 0;
    }
    // if we are in enigma string mode
    if(myState == Enigma_string_back || myState == Enigma_string_plug_back) {
        //reset the main options, starting on play
        options[0] = Enigma_char;
        options[1] = Enigma_string;
        options[2] = Exit;
        numOfOptions = 3;
        myStateNum = 1;

        // erase all the spites
        selected.unDraw();
        image.unDraw();
        wordImage.unDraw();
        encryptWordImage.unDraw();
        leftRImage.unDraw();
        midRImage.unDraw();
        rightRImage.unDraw();
        selectRotor.unDraw();

        // reset the word to encrypt
        word = "";

        // get and draw the menu file
        ifstream imageFile("Menu.txt");
        ifstream imageColorFile("MenuColor.txt");
        image.setX(0);
        image.setY(0);
        image.setImage(imageFile, imageColorFile);
        image.draw();

        // move and draw the selection bar
        ifstream selectFile("Selected.txt");
        selected.setImage(selectFile, white, center);
        selected.setX(SCREENWIDTH/2);
        selected.setY(SCREENHEIGHT/2-3);
        selected.draw();

        // set the current rotor settings
        encryption.setSetting3(encryption.getSetting3().c_str()[0]);
        encryption.setSetting2(encryption.getSetting2().c_str()[0]);
        encryption.setSetting1(encryption.getSetting1().c_str()[0]);
        currSelectRotor = 0;
    }
}

/*
Called when an alpha key is pressed

If the application is in enigma char mode, encrypt the character and display the
result, changing the rotor settings in the process.
If the application is in enigma char plugboard mode, add the setting to that
key. If the key is already taken, remove the old setting and start a new one.
If the application is in enigma string mode, add the char to the encryption
string.
If the application is in enigma string plugboard mode, add the setting to that
key. If the key is already taken, remove the old setting and start a new one.
*/
void Menu::keyPushed(char key) {
    States myState = options[myStateNum];
    if (myState == Enigma_char_back) {
        // erase the selection bar and the secondary selection bar
        selected.unDraw();
        second_selected.unDraw();

        // set the selection bar image
        ifstream selectFile("KeySelect.txt");
        selected.setImage(selectFile, green, center);
        selectFile.close();

        // move the selection bar depending on the key pressed
        switch(key) {
        case 'Q': case 'q': selected.setX(15); selected.setY(13); break;
        case 'W': case 'w': selected.setX(25); selected.setY(13); break;
        case 'E': case 'e': selected.setX(35); selected.setY(13); break;
        case 'R': case 'r': selected.setX(45); selected.setY(13); break;
        case 'T': case 't': selected.setX(55); selected.setY(13); break;
        case 'Y': case 'y': selected.setX(65); selected.setY(13); break;
        case 'U': case 'u': selected.setX(75); selected.setY(13); break;
        case 'I': case 'i': selected.setX(85); selected.setY(13); break;
        case 'O': case 'o': selected.setX(95); selected.setY(13); break;
        case 'P': case 'p': selected.setX(105); selected.setY(13); break;
        case 'A': case 'a': selected.setX(19); selected.setY(21); break;
        case 'S': case 's': selected.setX(29); selected.setY(21); break;
        case 'D': case 'd': selected.setX(39); selected.setY(21); break;
        case 'F': case 'f': selected.setX(49); selected.setY(21); break;
        case 'G': case 'g': selected.setX(59); selected.setY(21); break;
        case 'H': case 'h': selected.setX(69); selected.setY(21); break;
        case 'J': case 'j': selected.setX(79); selected.setY(21); break;
        case 'K': case 'k': selected.setX(89); selected.setY(21); break;
        case 'L': case 'l': selected.setX(99); selected.setY(21); break;
        case 'Z': case 'z': selected.setX(23); selected.setY(29); break;
        case 'X': case 'x': selected.setX(33); selected.setY(29); break;
        case 'C': case 'c': selected.setX(43); selected.setY(29); break;
        case 'V': case 'v': selected.setX(53); selected.setY(29); break;
        case 'B': case 'b': selected.setX(63); selected.setY(29); break;
        case 'N': case 'n': selected.setX(73); selected.setY(29); break;
        case 'M': case 'm': selected.setX(83); selected.setY(29); break;
        }
        // draw the selection bar
        selected.draw();

        // encrypt the char
        char new_key = encryption.encryptString(string(1, key))[0];

        // set the updated rotor settings
        leftRImage.setImage(encryption.getSetting3(), white, center);
        leftRImage.draw();
        midRImage.setImage(encryption.getSetting2(), white, center);
        midRImage.draw();
        rightRImage.setImage(encryption.getSetting1(), white, center);
        rightRImage.draw();

        // move the secondary selection bar depending on the encrypted char.
        switch(new_key) {
        case 'Q': case 'q': second_selected.setX(15); second_selected.setY(13); break;
        case 'W': case 'w': second_selected.setX(25); second_selected.setY(13); break;
        case 'E': case 'e': second_selected.setX(35); second_selected.setY(13); break;
        case 'R': case 'r': second_selected.setX(45); second_selected.setY(13); break;
        case 'T': case 't': second_selected.setX(55); second_selected.setY(13); break;
        case 'Y': case 'y': second_selected.setX(65); second_selected.setY(13); break;
        case 'U': case 'u': second_selected.setX(75); second_selected.setY(13); break;
        case 'I': case 'i': second_selected.setX(85); second_selected.setY(13); break;
        case 'O': case 'o': second_selected.setX(95); second_selected.setY(13); break;
        case 'P': case 'p': second_selected.setX(105); second_selected.setY(13); break;
        case 'A': case 'a': second_selected.setX(19); second_selected.setY(21); break;
        case 'S': case 's': second_selected.setX(29); second_selected.setY(21); break;
        case 'D': case 'd': second_selected.setX(39); second_selected.setY(21); break;
        case 'F': case 'f': second_selected.setX(49); second_selected.setY(21); break;
        case 'G': case 'g': second_selected.setX(59); second_selected.setY(21); break;
        case 'H': case 'h': second_selected.setX(69); second_selected.setY(21); break;
        case 'J': case 'j': second_selected.setX(79); second_selected.setY(21); break;
        case 'K': case 'k': second_selected.setX(89); second_selected.setY(21); break;
        case 'L': case 'l': second_selected.setX(99); second_selected.setY(21); break;
        case 'Z': case 'z': second_selected.setX(23); second_selected.setY(29); break;
        case 'X': case 'x': second_selected.setX(33); second_selected.setY(29); break;
        case 'C': case 'c': second_selected.setX(43); second_selected.setY(29); break;
        case 'V': case 'v': second_selected.setX(53); second_selected.setY(29); break;
        case 'B': case 'b': second_selected.setX(63); second_selected.setY(29); break;
        case 'N': case 'n': second_selected.setX(73); second_selected.setY(29); break;
        case 'M': case 'm': second_selected.setX(83); second_selected.setY(29); break;
        }
        // draw the secondary selection bar
        second_selected.draw();
    }
    else if (myState == Enigma_char_plug_back) {
        asmToLower(&key);
        if(firstPlugChar.length() == secondPlugChar.length()) {
            if (firstPlugChar.length() < 10) {
                firstPlugChar += key;
                plugString = "";
                for(int i=0; i<secondPlugChar.length(); i++) {
                    plugString += firstPlugChar[i];
                    plugString += " - ";
                    plugString += secondPlugChar[i];
                    plugString += "\n";
                }
                plugString += firstPlugChar[firstPlugChar.length()-1];
                plugString += " : ";
                plugChars.setImage(plugString, white);
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
                plugString = "";
                for(int i=0; i<secondPlugChar.length(); i++) {
                    plugString += firstPlugChar[i];
                    plugString += " - ";
                    plugString += secondPlugChar[i];
                    plugString += "\n";
                }
                plugChars.setImage(plugString, white);
                plugChars.draw();
            }
        }
    }
    else if (myState == Enigma_string_back) {
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
    else if (myState == Enigma_string_plug_back) {
        asmToLower(&key);
        if(firstPlugChar.length() == secondPlugChar.length()) {
            if (firstPlugChar.length() < 10) {
                firstPlugChar += key;
                plugString = "";
                for(int i=0; i<secondPlugChar.length(); i++) {
                    plugString += firstPlugChar[i];
                    plugString += " - ";
                    plugString += secondPlugChar[i];
                    plugString += "\n";
                }
                plugString += firstPlugChar[firstPlugChar.length()-1];
                plugString += " : ";
                plugChars.setImage(plugString, white);
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
                plugString  = "";
                for(int i=0; i<secondPlugChar.length(); i++) {
                    plugString += firstPlugChar[i];
                    plugString += " - ";
                    plugString += secondPlugChar[i];
                    plugString += "\n";
                }
                plugChars.setImage(plugString, white);
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
void Menu::moveUp() {
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
void Menu::moveLeft() {
    States myState = options[myStateNum];
    if(myState == Enigma_char_back || myState == Enigma_string_back || myState == Enigma_char_plug_back || myState == Enigma_string_plug_back) {
        currSelectRotor = (currSelectRotor+2)%3;
        selectRotor.unDraw();
        selectRotor.setX(129+currSelectRotor*10);
        selectRotor.draw();
    }
}

//called if right is pressed
void Menu::moveRight() {
    States myState = options[myStateNum];
    if(myState == Enigma_char_back || myState == Enigma_string_back || myState == Enigma_char_plug_back || myState == Enigma_string_plug_back) {
        currSelectRotor = (currSelectRotor+1)%3;
        selectRotor.unDraw();
        selectRotor.setX(129+currSelectRotor*10);
        selectRotor.draw();
    }
}

//called if down is pressed
void Menu::moveDown() {
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
