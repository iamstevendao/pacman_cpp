#include "Character.h"

Character::Character(int x, int y) : Element(x, y) {}

int Character::getX(){
	return Element::getX();
}
int Character::getY(){
	return Element::getY();
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