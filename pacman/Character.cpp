#include "Character.h"

Character::Character(int x, int y, Color color) : Element(x, y, color) {}

int Character::getX(){
	return Element::getX();
}
int Character::getY(){
	return Element::getY();
}
Color Character::getColor(){
	return Element::getColor();
}
void Character::goLeft(){
	if(_x > 0) _x--;
}
void Character::goRight(){
	_x++;
}
void Character::goUp(){
	if(_y>0) _y--;
}
void Character::goDown(){
	_y++;	
}