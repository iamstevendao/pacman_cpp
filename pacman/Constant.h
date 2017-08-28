#include <SFML/Graphics.hpp>

#ifndef CONSTANT_H
#define CONSTANT_H

#define WIDTH_ELEMENT 40
#define HEIGHT_ELEMENT 40
#define SIZE_GRID 19
#define WIDTH_WINDOW 760
#define HEIGHT_WINDOW 760
#define NUMBER_GHOST 8
#define NUMBER_GHOST_COLOR 5
#define NUMBER_INTERVAL 80
#define NUMBER_POWER 50
#define NUMBER_CHERRY 5
#define TEXT_PACMAN_X WIDTH_WINDOW/4
#define TEXT_PACMAN_Y HEIGHT_WINDOW/4
#define TEXT_SCORE_X WIDTH_WINDOW/4 + 100
#define TEXT_SCORE_Y HEIGHT_WINDOW/4 + 100
#define TEXT_PLAY_X WIDTH_WINDOW/4 + 100
#define TEXT_PLAY_Y HEIGHT_WINDOW/4 + 200 
#define TEXT_EXIT_X WIDTH_WINDOW/4 + 100
#define TEXT_EXIT_Y HEIGHT_WINDOW/4 + 300

#define COLOR_BACKGROUND Color::Black
#define COLOR_MAP Color::Blue
#define COLOR_FOOD Color::White
#define COLOR_PACMAN Color::Red
#define COLOR_POWER Color::Yellow
#define COLOR_GHOST Color::Yellow
#define COLOR_CHERRY Color::Red
#define COLOR_CHERRY_BRANCH Color::Green

class Constant {
public:
	enum GhostArea { x = 7, y = 8, w = 5, h = 3 };
	static const Color GhostColors(int index) {
		static const Color a[] = {Color::Cyan,Color::Blue,Color::Yellow, Color::Magenta, Color::Green};
		return a[index];
	}
	enum Direction { left, right, up, down };
};

#endif
