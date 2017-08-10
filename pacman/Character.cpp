#include "Character.h"
int Character::getX(){
	return x;
}
int Character::getY(){
	return y;
}
void Character::goLeft(){
	if(x > 0) x--;
}
void Character::goRight(){
	x++;
}
void Character::goUp(){
	if(y>0) y--;
}
void Character::goDown(){
	y++;	
}