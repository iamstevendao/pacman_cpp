#include "Element.h"
#ifndef CHARACTER_H
#define CHARACTER_H

#define CHARACTER_WIDTH 100
#define CHARACTER_HEIGHT 100
class Character : public Element {
public:
	Character(int, int, Color);
	int getX();
	int getY();
	Color getColor();
	void goLeft();
	void goRight();
	void goUp();
	void goDown();
};

#endif
