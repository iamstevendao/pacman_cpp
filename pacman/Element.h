#include <SFML/Graphics.hpp>
using namespace sf;

#ifndef ELEMENT_H
#define ELEMENT_H
class Element {
protected:
	float _x;
	float _y;
	int _width;
	int _height;
	Color _color;
public:
	Element();
	Element(float,float,Color);
	void setX(float);
	void setY(float);
	float getX();
	float getY();
	int getWidth();
	int getHeight();
	Color getColor();
};

#endif