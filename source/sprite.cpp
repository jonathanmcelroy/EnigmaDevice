/******************************************************************************
Author:             Jonathan McElroy
Filename:           sprite.cpp
Description:        A class for sprites
Date Modified:      11/20/2012
******************************************************************************/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "constants.h"
#include "sprite.h"
#include "plotter.h"

//initializer
Sprite::Sprite()
{
}

/******************************************************************************
initiates an object at (x,y) with the image string

the string object must be a series of lines seperated by '\n's
i.e. "first line\nsecond line\netc"
if there is a ' ', it will write over whatever is there
if there is a '~', it will not write over that spot
the color will default to white
******************************************************************************/
Sprite::Sprite(double newX, double newY, string newImage, Place pos /* = topRight */)
{
    x = newX;
    y = newY;
    setImage(newImage, white, pos);
}

/******************************************************************************
initiates an object at (x,y) from a file and a color file

it will draw whatever is in the file in the color of the coresponding spot in
the color file. If the color file has a blank spot, that spot will be black
******************************************************************************/
Sprite::Sprite(double newX, double newY, ifstream &newImage, ifstream &newColor, Place pos /* = topRight */)
{
    x = newX;
    y = newY;
    setImage(newImage, newColor, pos);
}

//destroctor
Sprite::~Sprite()
{
    //will remove the image from the console
    unDraw();
}

//modifiers
void Sprite::setX(double newX)
{
    x = newX;
}
void Sprite::setY(double newY)
{
    y = newY;
}
//this will move the sprite, but also update the image
void Sprite::move(double newX, double newY)
{
    unDraw();
    x = newX;
    y = newY;
    draw();
}
//this sets the image to a string
void Sprite::setImage(string newImage, ink c /*= white*/, Place pos /* = topRight */)
{
    //sets the place and color
    place = pos;
    solidColor = c;
    //resets the internal image storage to nulls
    for(unsigned int i = 0;i<SCREENHEIGHT;i++)
    {
        for(unsigned int j = 0;j<SCREENWIDTH;j++)
        {
            image[i][j] = 0;
        }
    }
    //resets the internal color storage to black
    for(unsigned int i = 0;i<SCREENHEIGHT;i++)
    {
        for(unsigned int j = 0;j<SCREENWIDTH;j++)
        {
            color[i][j] = black;
        }
    }
    //the width and height start at (1,1)
    width = height = 1;
    //the row and column of the internal storage
    int row = 0, col = 0;
    //go through all the characters in the string
    for(int i=0;i<newImage.length();i++)
    {
        //if the char is not a newline
        if(newImage[i]!='\n')
        {
            //if the char is not a tilde
            if(newImage[i]!='~')
            {
                //set the array pos to be the char
                image[row][col] = newImage[i];
                //set the color array pos to be the color
                color[row][col] = c;
            }
            //increment the column
            col++;
            //if we are further then we have gone
            if(col>width)
            {
                //increase the width
                width++;
            }
        }
        //if the char is a newline
        else
        {
            //go one down, start at the beginning of the line and increase the height
            row++;
            height++;
            col = 0;
        }
    }
}
//this sets the graphic using a text file with the image and a certain color
void Sprite::setImage(ifstream &newImage, ink c, Place pos /* = topLeft */)
{
    //sets the place
    place = pos;
    solidColor = c;
    //resets the internal image storage to nulls
    for(unsigned int i = 0;i<SCREENHEIGHT;i++)
    {
        for(unsigned int j = 0;j<SCREENWIDTH;j++)
        {
            image[i][j] = 0;
        }
    }
    //resets the internal color storage to black
    for(unsigned int i = 0;i<SCREENHEIGHT;i++)
    {
        for(unsigned int j = 0;j<SCREENWIDTH;j++)
        {
            color[i][j] = black;
        }
    }
    //the width and height start at (1,1)
    width = height = 1;
    //the row and column of the internal storage
    int row = 0, col = 0;

    //the char in the file and color file
    char ch;
    //while we grab new characters
    while(newImage.get(ch))
    {
		if (ch < 0) continue;
        //if the char is not a newline
        if(ch!='\n')
        {
            //if the char is not a tilde
            if(ch!='~' && isprint(ch))
            {
                //set the array pos to be the chars
                image[row][col] = ch;
                color[row][col] = c;
                //set the color array pos to be the color
            }
            //increment the column
            col++;
            //if we are further then we have gone
            if(col>width)
            {
                //increase the width
                width++;
            }
        }
        //if the char is a newline
        else
        {
            //go one down, start at the beginning of the line and increase the height
            row++;
            height++;
            col = 0;
        }
    }
}
//this sets the graphic using a text file with the image and a text file with the colors
void Sprite::setImage(ifstream &newImage, ifstream &newColor, Place pos /* = topLeft */)
{
    //sets the place
    place = pos;
    //resets the internal image storage to nulls
    for(unsigned int i = 0;i<SCREENHEIGHT;i++)
    {
        for(unsigned int j = 0;j<SCREENWIDTH;j++)
        {
            image[i][j] = 0;
        }
    }
    //resets the internal color storage to black
    for(unsigned int i = 0;i<SCREENHEIGHT;i++)
    {
        for(unsigned int j = 0;j<SCREENWIDTH;j++)
        {
            color[i][j] = black;
        }
    }
    //the width and height start at (1,1)
    width = height = 1;
    //the row and column of the internal storage
    int row = 0, col = 0;

    //the char in the file and color file
    char ch, chColor;
    //while we grab new characters
    while(newImage.get(ch))
    {
        //grab a color char
        newColor.get(chColor);
		if (ch < 0) continue;
        //if the char is not a newline
        if(ch!='\n')
        {
            //if the char is not a tilde
            if(ch!='~' && isprint(ch))
            {
                //set the array pos to be the chars
                image[row][col] = ch;
                //set the color array pos to be the color
                switch(chColor)
                {
                    //B maps to blue
                    case 'B':
                    case 'b':
                        color[row][col] = blue;
                        break;
                    //C maps to cyan
                    case 'C':
                    case 'c':
                        color[row][col] = cyan;
                        break;
                    //G maps to green
                    case 'G':
                    case 'g':
                        color[row][col] = green;
                        break;
                    //R maps to red
                    case 'R':
                    case 'r':
                        color[row][col] = red;
                        break;
                    //S maps to darkyellow
                    case 'S':
                    case 's':
                        color[row][col] = darkyellow;
                        break;
                    //Y maps to yellow
                    case 'Y':
                    case 'y':
                        color[row][col] = yellow;
                        break;
                    //W maps to white
                    case 'W':
                    case 'w':
                        color[row][col] = white;
                        break;
                    //the defaul color is black
                    default:
                        color[row][col] = black;
                }
            }
            //increment the column
            col++;
            //if we are further then we have gone
            if(col>width)
            {
                //increase the width
                width++;
            }
        }
        //if the char is a newline
        else
        {
            //go one down, start at the beginning of the line and increase the height
            row++;
            height++;
            col = 0;
        }
    }
}
//this sets the color of the image to a single color
void Sprite::setColor(ink c)
{
    solidColor = c;
    //go through the internal storage
    for(unsigned int i = 0;i<SCREENHEIGHT;i++)
    {
        for(unsigned int j = 0;j<SCREENWIDTH;j++)
        {
            //where the image has a char, set the color to c
            if(image[i][j] != 0)
            {
                color[i][j] = c;
            }
        }
    }
}
//this sets the color of the image to a matrix of colors represented by a string
void Sprite::setColor(string c)
{
    //the row and column of the internal storage
    int row = 0, col = 0;
    //go through each char in the string
    for(unsigned int i=0;i<c.length();i++)
    {
        //if the char is not a newline
        if(c[i]!='\n')
        {
            //set the color array pos to be the color
            switch(c[i])
            {
                //B maps to blue
                case 'B':
                case 'b':
                    color[row][col] = blue;
                    break;
                //C maps to cyan
                case 'C':
                case 'c':
                    color[row][col] = cyan;
                    break;
                //G maps to green
                case 'G':
                case 'g':
                    color[row][col] = green;
                    break;
                //R maps to red
                case 'R':
                case 'r':
                    color[row][col] = red;
                    break;
                //S maps to darkyellow
                case 'S':
                case 's':
                    color[row][col] = darkyellow;
                    break;
                //Y maps to yellow
                case 'Y':
                case 'y':
                    color[row][col] = yellow;
                    break;
                //W maps to white
                case 'W':
                case 'w':
                    color[row][col] = white;
                    break;
                //the default color is black
                default:
                    color[row][col] = black;
            }
            //increment the column
            col++;
        }
        //if the char is a newline
        else
        {
            //go one down and start at the beginning of the line
            row++;
            col = 0;
        }
    }
}
void Sprite::setPlace(Place pos)
{
    place = pos;
}

//accessors
double Sprite::getX()
{
    return x;
}
double Sprite::getY()
{
    return y;
}
//this only works if setColor(ink) is the last color related modifier called
ink Sprite::getColor()
{
    return solidColor;
}
Place Sprite::getPlace()
{
    return place;
}

//moves the x based on the place drawn
int Sprite::transformX(int xPos)
{
    switch(place)
    {
        //if on the left, keep the same place
        case topLeft:
        case midLeft:
        case bottomLeft:
            return xPos;
        //if in the middle, move over half the width or until the edge of the screen
        case topMiddle:
        case center:
        case bottomMiddle:
            return (x-width/2 > 0) ? xPos-width/2 : xPos - x;
        //if on the right, move over the full wdth or until the edge of the screen
        case topRight:
        case midRight:
        case bottomRight:
            return (x-width > 0) ? xPos-width : xPos - x;
    }
}
//moves the x based on the place drawn
int Sprite::transformY(int yPos)
{
    switch(place)
    {
        //if on the top, keep the same place
        case topLeft:
        case topMiddle:
        case topRight:
            return yPos;
        //if in the middle, move up half the height or until the edge of the screen
        case midLeft:
        case center:
        case midRight:
            return (y-height/2) ? yPos-height/2 : yPos - y;
        //if on the right, move up the full height or until the edge of the screen
        case bottomLeft:
        case bottomMiddle:
        case bottomRight:
            return (y-height) ? yPos-height : yPos - y;
    }
}

//draws an object to the console using the plotter
//uses a buffer system to write faster
void Sprite::draw()
{
    //the buffer
    string buffer;
    ink myColor = black;
	plot.move(transformX(x),transformY(y));
    //this goes through all the characters in the image
    for(unsigned int i = 0;i<height;i++)
    {
        for(unsigned int j = 0;j<width;j++)
        {
            //if the image char is null or the color is black
            if(image[i][j]==0 || color[i][j]==black)
            {
                //write the buffer if there is one
                if(buffer.length()>0)
                {
                    plot.setColor(myColor);
                    cout << buffer;
                    buffer = "";
                    myColor = black;
                }
            }
            //if the image is a non-black char
            else
            {
                //if the color has changed since the last color
                if(color[i][j]!=myColor)
                {
                    //if there is a buffer, write it
                    if(buffer.length()>0)
                    {
                        plot.setColor(myColor);
                        cout << buffer;
                        buffer = "";
                    }
                    //change the color
                    myColor = color[i][j];
                    //move the cursor to the current pos
                    plot.move(transformX(x+j),transformY(y+i));
                }
                //add the image char to the buffer
                buffer += image[i][j];
            }
        }
        //if we get to the end of a line with a buffer, write it and set the color to black
        if(buffer.length()>0)
        {
            plot.setColor(myColor);
            cout << buffer;
            buffer = "";
            plot.move(transformX(x),transformY(y+i)+1);
            myColor = black;
        }
    }
}
//erases the image from the console
void Sprite::unDraw()
{
	string buffer;
	ink myColor = black;
	plot.move(transformX(x),transformY(y));
    //for all the chars in the image
    for(unsigned int i = 0;i<height;i++)
    {
        for(unsigned int j = 0;j<width;j++)
        {
            //if a null char
            if(image[i][j]==0)
			{
				if(buffer.length()>0)
                {
                    cout << buffer;
                    buffer = "";
                    myColor = black;
                }
			}
			else
            {
				if(myColor==black) {
					myColor = white;
					plot.move(transformX(x+j),transformY(y+i));
				}
                //overwrite what is on the console
                buffer+=' ';
            }
        }
		if(buffer.length()>0) {
			cout << buffer;
			buffer = "";
			plot.move(transformX(x),transformY(y+i)+1);
			myColor = black;
		}
    }
}
