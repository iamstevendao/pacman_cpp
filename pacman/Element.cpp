#include "Element.h"
Element::Element(int x,int y, Color color){
	_x = x;
	_y = y;
	_color = color;
}
int Element::getX(){
	return _x;
}
int Element::getY(){
	return _y;
}

Color Element::getColor(){
	return _color;
}