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

#define COLOR_MAP Color::Blue
#define COLOR_FOOD Color::White
#define COLOR_PACMAN Color::Red
#define COLOR_GHOST Color::Yellow

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
