#include "Element.h"
#include "Constant.h"

#ifndef CHARACTER_H
#define CHARACTER_H

#define CHARACTER_WIDTH 100
#define CHARACTER_HEIGHT 100

struct Point {
	float x;
	float y;
	Point() {}
	Point(float a, float b) : x(a), y(b) {}
};

struct Path {
	Point point;
	Path *next;
};

class Character : public Element {
private:
	Constant::Direction _direction;
	Path *_head;
	int _target;
	int _id;
public:
	Character();
	Character(float, float, Color);
	Constant::Direction getDirection();
	void setDirection(Constant::Direction);
	float round(float);

	void setId(int);
	int getTarget();
	void setTarget(int);
	void goLeft();
	void goRight();
	void goUp();
	void goDown();

	//new
	void setPath(Path *head);
	Path* getPath();
	void updateHead();
	void followPath();
	void resetPath();
	//void update(Point);
	//Path* findPath(Point);
	//void updatePath(Point);
	//vector<Point> getAdjacences(vector<Path>, Point);
};

#endif
