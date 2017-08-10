#include "Constant.h"

#ifndef ELEMENT_H
#define ELEMENT_H
class Element {
protected:
	int _x;
	int _y;
	int _width;
	int _height;
	Constant::Color _color;
public:
	Element(int,int);
	int getX();
	int getY();
	int getWidth();
	int getHeight();
	Constant::Color getColor();
};

#endif