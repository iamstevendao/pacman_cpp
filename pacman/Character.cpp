#include "Character.h"

Character::Character() {}
Character::Character(float x, float y, Color color) : Element(x, y, color) {}

Color Character::getColor(){
	return Element::getColor();
}

void Character::goLeft(){
	if(_x > 0) _x-=1/4;
	_y = round(_y);
}

void Character::goRight(){
	_x+=1/4;
	_y = round(_y);
}

void Character::goUp() {
	if(_y>0) _y-=1/4;
	_x = round(_x);
}

void Character::goDown() {
	_y+=1/4;	
	_x = round(_y);
}

Constant::Direction Character::getDirection(){
	return _direction;
}

void Character::setDirection(Constant::Direction direction){
	_direction = direction;
}

int Character::round(float x) {
	if(ceil(x - 0.5) == ceil(x)) 
		return ceil(x);
	else 
		return floor(x);
}