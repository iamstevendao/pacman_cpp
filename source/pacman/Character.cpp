#include "Character.h"
#include <vector>
using namespace std;

Character::Character() {}
Character::Character(float x, float y, Color color) : Element(x, y, color) {
	resetPath();
}

#pragma region Getter Setter
Constant::Direction Character::getDirection(){
	return _direction;
}

void Character::setDirection(Constant::Direction direction){
	_direction = direction;
}
#pragma endregion

#pragma region Move
void Character::goLeft(){
	if(_x > 0) _x-=(float)1/4;
	_y = round(_y);
}

void Character::goRight(){
	_x+=(float)1/4;
	_y = round(_y);
}

void Character::goUp() {
	if(_y>0) _y-=(float)1/4;
	_x = round(_x);
}

void Character::goDown() {
	_y+=(float)1/4;	
	_x = round(_x);
}

//Path* Character::findPath(Point destination){
//	if(destination.x == _head->point.x && destination.y == _head->point.y) {
//		setPath(NULL);
//	}
//	vector<Path> queue;
//	queue.push_back(*_head);
//	int index = 0;
//	Path *result = NULL;
//	while(!result) {
//		vector<Point> adj = getAdjacences(queue, queue[index].point);
//		for(int i = 0; i < adj.size(); i++) {
//			Path *path = new Path();
//			path->point = adj[i];
//			path->next = &queue[index];
//			queue.push_back(*path);
//			if(adj[i].x == destination.x && adj[i].y == destination.y)
//				result = path;
//		}
//		index++;
//	}
//	return result;
//}
//
//vector<Point> Character::getAdjacences(vector<Path> queue, Point point) {
//	vector<Point> adj;
//	adj.push_back(Point(point.x, point.y - 1));
//	adj.push_back(Point(point.x, point.y + 1));
//	adj.push_back(Point(point.x - 1, point.y));
//	adj.push_back(Point(point.x + 1, point.y));
//	adj = shuffle(ind, adj);
//	for(int i = 0; i < adj.size(); i++) {
//		if(adj[i].x < 1 || adj[i].y < 1 || 
//			adj[i].x > SIZE_GRID || adj[i].y > SIZE_GRID ||
//			isInMap(point) || isInQueue(queue, point)) {
//			adj.erase(adj.begin() + i);
//			i--;
//		}
//	}
//	return adj;
//}
void Character::resetPath() {
	_head = new Path;
	_head->point = Point(_x, _y);
	_head->next = 0;
}
void Character::setPath(Path *head){
	head->next = head;
}

Path* Character::getPath(){
	return _head;
}

void Character::updateHead() {
	_head->point = Point(_x, _y);
}

void Character::setId(int id) {
	_id = id;
}

void Character::followPath(){
	if(_head->next) {
		Point point = _head->next->point;
		if(_x == point.x) {
			_direction = point.y > _y ? Constant::Direction::down : Constant::Direction::up;
		} else {
			_direction = point.x > _x ? Constant::Direction::right : Constant::Direction::left;
		}
	}
}

//void Character::update(Point destination) {
//	updateHead();
//	updatePath();
//}
#pragma endregion

int Character::getTarget(){
	return _target;
}
void Character::setTarget(int target){
	_target = target;
}
float Character::round(float x) {
	if(ceil(x - 0.5) == ceil(x)) 
		return ceil(x);
	else 
		return floor(x);
}