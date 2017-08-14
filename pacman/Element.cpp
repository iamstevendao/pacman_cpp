#include "Element.h"
Element::Element() {}
Element::Element(float x,float y, Color color){
	_x = x;
	_y = y;
	_color = color;
}
float Element::getX(){
	return _x;
}
float Element::getY(){
	return _y;
}
void Element::setX(float x){
	_x = x;
}
void Element::setY(float y) {
	_y = y;
}
Color Element::getColor(){
	return _color;
}