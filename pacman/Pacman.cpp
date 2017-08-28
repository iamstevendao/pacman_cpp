#include "Pacman.h"
Pacman::Pacman(){}
Pacman::Pacman(int x, int y, Color color): Character(x,y,color){
	_isOpen = true;
	_power = 0;
}
bool Pacman::switchOpen(){
	_isOpen = !_isOpen;
	return _isOpen;
}
int Pacman::getPower(){
	return _power;
}
void Pacman::activatePower() {
	_power = NUMBER_INTERVAL * NUMBER_POWER;
}
void Pacman::reducePower(){
	_power -= NUMBER_INTERVAL;
}