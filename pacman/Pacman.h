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
	bool switchOpen();
	int getPower();
	void activatePower();
	void reducePower();
};

#endif