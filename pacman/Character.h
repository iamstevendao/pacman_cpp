#include "Element.h"
#include "Constant.h"

#ifndef CHARACTER_H
#define CHARACTER_H

#define CHARACTER_WIDTH 100
#define CHARACTER_HEIGHT 100
class Character : public Element {
private:
	Constant::Direction _direction;
	
public:
	Character();
	Character(float, float, Color);
	Constant::Direction getDirection();
	void setDirection(Constant::Direction);
	float round(float);
	Color getColor();
	void goLeft();
	void goRight();
	void goUp();
	void goDown();
};

#endif
