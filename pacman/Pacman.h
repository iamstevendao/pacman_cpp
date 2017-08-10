#include "Character.h"

#ifndef PACMAN_H
#define PACMAN_H
class Pacman : public Character{
private:
	bool isOpen;
public:
	Pacman();
	Pacman(int, int, Color);
	bool getIsOpen();
	/*int getX();
	int getY();
	Color getColor();
	void goLeft();
	void goRight();
	void goUp();
	void goDown();*/
};

#endif