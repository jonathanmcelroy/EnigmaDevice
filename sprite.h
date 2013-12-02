#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include <string>
#include <fstream>
#include "constants.h"
#include "plotter.h"

using namespace std;

//the places the images may be drawn from relative to the (x,y)
enum Place
{
    topLeft,    topMiddle,    topRight,
    midLeft,    center,       midRight,
    bottomLeft, bottomMiddle, bottomRight
};

//a class that stars an array and draws it
class Sprite
{
    private:
        //the (x,y) and the width and height of the image
        double x, y, width, height;
        //the array holding the drawing imformation
        char image[SCREENHEIGHT][SCREENWIDTH];
        //the array holding the color information
        ink color[SCREENHEIGHT][SCREENWIDTH];
        //the plotter object for drawing
        Plotter plot;
        //if there is only one set color, the returns it
        ink solidColor;
        //the place the image is draw from
        Place place;
    public:
        //initializers
        Sprite();
        //initiates a sprite at (x,y) with the image string
        Sprite(double,double,string, Place = topLeft);
        //initiates a sprite at (x,y) from a file
        Sprite(double,double,ifstream &,ifstream &, Place = topLeft);

        //destructor
        ~Sprite();

        //modifiers
        void setX(double);
        void setY(double);
        void move(double, double);
        void setImage(string, ink = white, Place = topLeft);
        void setImage(ifstream &, ink = white, Place = topLeft);
        void setImage(ifstream &, ifstream &, Place = topLeft);
        void setColor(ink);
        void setColor(string);
        void setPlace(Place);

        //accessors
        double getX();
        double getY();
        ink getColor();
        Place getPlace();

        //moves the (x,y) based on the place drawn
        int transformX(int);
        int transformY(int);

        //draws the sprite using the plotter
        void draw();
        void unDraw();
};

#endif // OBJECT_H_INCLUDED
