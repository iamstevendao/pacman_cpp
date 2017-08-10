#include <SFML/Graphics.hpp>
using namespace sf;

#ifndef ELEMENT_H
#define ELEMENT_H
class Element {
protected:
	int _x;
	int _y;
	int _width;
	int _height;
	Color _color;
public:
	Element(int,int,Color);
	int getX();
	int getY();
	int getWidth();
	int getHeight();
	Color getColor();
};

#endif