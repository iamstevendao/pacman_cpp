#include "Element.h"
Element::Element(int x,int y){
	_x = x;
	_y = y;
}
int Element::getX(){
	return _x;
}
int Element::getY(){
	return _y;
}
Constant::Color Element::getColor(){
	return _color;
}