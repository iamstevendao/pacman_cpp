#ifndef CONSTANT_H
#define CONSTANT_H

#define WIDTH_ELEMENT 40
#define HEIGHT_ELEMENT 40
#define SIZE_GRID 19
#define WIDTH_WINDOW 760
#define HEIGHT_WINDOW 760
#define NUMBER_GHOST 8

class Constant {
public:
	enum Color {red, green, blue};
	enum GhostArea { x = 7, y = 8, w = 5, h = 3 };
};

#endif
