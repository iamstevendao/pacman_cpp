#include "Character.h"

Character::Character() {}
Character::Character(float x, float y, Color color) : Element(x, y, color) {}

#pragma region Getter Setter
Color Character::getColor(){
	return Element::getColor();
}

Constant::Direction Character::getDirection(){
	return _direction;
}

void Character::setDirection(Constant::Direction direction){
	_direction = direction;
}
#pragma endregion

#pragma region Move
void Character::goLeft(){
	if(_x > 0) _x-=(float)1/4;
	_y = round(_y);
}

void Character::goRight(){
	_x+=(float)1/4;
	_y = round(_y);
}

void Character::goUp() {
	if(_y>0) _y-=(float)1/4;
	_x = round(_x);
}

void Character::goDown() {
	_y+=(float)1/4;	
	_x = round(_x);
}
#pragma endregion

float Character::round(float x) {
	if(ceil(x - 0.5) == ceil(x)) 
		return ceil(x);
	else 
		return floor(x);
}