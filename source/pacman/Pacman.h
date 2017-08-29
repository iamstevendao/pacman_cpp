#include "Character.h"

#ifndef PACMAN_H
#define PACMAN_H
class Pacman : public Character{
private:
	bool _isOpen;
	int _power;
public:
	Pacman();
	Pacman(int, int, Color);
	//toggle open and return
	bool toggleOpen();
	int getPower();
	//activate power when eats cherry
	void activatePower();
	//reduce power over time
	void reducePower();
};

#endif