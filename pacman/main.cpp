#include <SFML/Graphics.hpp>
#include "main.h"
#include <iostream>
#include <Windows.h>

using namespace std;

void generate();
void generateFood();
void generateGhost();
void generatePacman();
void generateMap();

void draw(sf::RenderWindow &);
void drawMap(sf::RenderWindow &);
void drawFood(sf::RenderWindow &);
void drawPacman(sf::RenderWindow &);
void drawGhosts(sf::RenderWindow &);

void controlGame();
void controlObject(Character &, bool);
void controlScore();


void pushToMap(int,int); 
void pushMultipleToMap(int,int); 
bool isContained(vector<Element>, Element);
bool isContained(vector<Character>, Character);
bool isContained(vector<Constant::Direction>, Constant::Direction);
bool isCrashed(float, float);
Constant::Direction opositeOf(Constant::Direction);
vector<Constant::Direction> whereCanGo(float,float);

vector<Element> maps;
vector<Element> foods;
vector<Character> ghosts;
Pacman pacman;

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
{
	sf::RenderWindow window(sf::VideoMode(760, 760), "SFML works!");
	//sf::CircleShape shape(100.f);
	//sf::RectangleShape rectangle(sf::Vector2f(120, 50));
	// shape.setFillColor(sf::Color::Green);
	generate();
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// window closed
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;
			case Event::KeyPressed: {
				switch(event.key.code) {
				case Keyboard::Left:
					pacman.setDirection(Constant::Direction::left);
					pacman.setY(pacman.round(pacman.getY()));
					break;
				case Keyboard::Right:
					pacman.setDirection(Constant::Direction::right);
					pacman.setY(pacman.round(pacman.getY()));
					break;
				case Keyboard::Up:
					pacman.setDirection(Constant::Direction::up);
					pacman.setX(pacman.round(pacman.getX()));
					break;
				case Keyboard::Down:
					pacman.setDirection(Constant::Direction::down);
					pacman.setX(pacman.round(pacman.getX()));
					break;
				}
									}
									break;
			default:
				break;
			}
		}

		window.clear();
		//   window.draw(shape);
		//	window.draw(rectangle);
		draw(window);
		controlGame();
		window.display();
		Sleep(80);
	}

	return 0;
}
//Question: isContained to generic type
bool isContained(vector<Element> list, Element ele) {
	for(int i = 0; i < list.size(); i++) {
		if(list[i].getX() == ele.getX() && list[i].getY() == ele.getY())
			return true;
	}
	return false;
}

bool isContained(vector<Character> list, Character ele) {
	for(int i = 0; i < list.size(); i++) {
		if(list[i].getX() == ele.getX() && list[i].getY() == ele.getY())
			return true;
	}
	return false;
}

bool isContained(vector<Constant::Direction> list, Constant::Direction ele) {
	if(find(list.begin(), list.end(), ele) != list.end()) 
		/* v contains x */
		return true;
	else 
		/* v does not contain x */
		return false;

}

void generate(){
	generateMap();
	generateFood();
	generateGhost();
	generatePacman();
}

void generateMap() {
	int k = SIZE_GRID /2;
	for(int i = 0; i < SIZE_GRID /2 + 1;i++)
		pushMultipleToMap(i, 0);
	for(int i = 1; i < SIZE_GRID /2 + 1; i++) 
		pushMultipleToMap(0,i);
	for(int i = 2; i < 7; i++) 
		pushMultipleToMap(2,i);
	for(int i = 4; i < 9; i++) 
		pushMultipleToMap(i,2);
	for(int i = 2; i < 5; i++) 
		pushMultipleToMap(i,8);
	for(int i = 4; i < 9; i+=2)
		for(int j = 4; j < 6; j++)
			pushMultipleToMap(i,j);
	pushMultipleToMap(4,7);
	pushMultipleToMap(7,7);
	pushMultipleToMap(6,7);
	pushMultipleToMap(6,8);
	pushToMap(6,9);
	pushToMap(SIZE_GRID - 6 - 1, 9);
	for(int i = 8; i < 11; i++)
		pushToMap(i, 11);
}
void pushMultipleToMap(int x, int y) {
	pushToMap(x, y);
	pushToMap(SIZE_GRID - x - 1, y);
	pushToMap(x, SIZE_GRID - y - 1);
	pushToMap(SIZE_GRID - x - 1, SIZE_GRID - y - 1);
}
void pushToMap(int x, int y) {
	Element block = Element(x, y, COLOR_MAP);
	maps.push_back(block);
}
void generateFood(){
	for(int i = 0; i < SIZE_GRID; i++) {
		for(int j = 0; j < SIZE_GRID; j++) {
			Element ele = Element(i, j, COLOR_FOOD);
			if(!isContained(maps, ele)) {
				foods.push_back(ele);
			}
		}
	}
}
void generateGhost(){
	for(int i = 0; i < 8; i++) {
		int x = rand() % Constant::GhostArea::w + Constant::GhostArea::x;
		int y = rand() % Constant::GhostArea::h + Constant::GhostArea::y;
		int color = rand() % NUMBER_GHOST_COLOR;

		Character ghost = Character(x, y, Constant::GhostColors(color));
		if(!isContained(ghosts, ghost))
			ghosts.push_back(ghost);
		else 
			i--;
	}
}
void generatePacman(){
	pacman = Pacman(1,1, COLOR_PACMAN);
	pacman.setDirection(Constant::Direction::right);
}

void draw(sf::RenderWindow &win) {
	drawMap(win);
	drawFood(win);
	drawGhosts(win);
	drawPacman(win);
}

void drawPacman(sf::RenderWindow &win) {
	float x = pacman.getX() * WIDTH_ELEMENT;
	float y = pacman.getY() * HEIGHT_ELEMENT;
	float x1 = x, x2 = x, y1 = y, y2 = y; //for the mouth
	float eyex = x, eyey = y; //for the eye
	switch(pacman.getDirection()) {
	case Constant::Direction::left:
		y2 += HEIGHT_ELEMENT;
		eyex += WIDTH_ELEMENT * 3/8;
		eyey += HEIGHT_ELEMENT / 8;
		break;
	case Constant::Direction::right:
		x1 = x2 += WIDTH_ELEMENT;
		y2 += WIDTH_ELEMENT;
		eyex += WIDTH_ELEMENT * 3/8;
		eyey += HEIGHT_ELEMENT / 8;
		break;
	case Constant::Direction::up:
		x2 += WIDTH_ELEMENT;
		eyex += WIDTH_ELEMENT /8;
		eyey += HEIGHT_ELEMENT * 3 / 8;
		break;
	case Constant::Direction::down:
		x2 += WIDTH_ELEMENT;
		y1 = y2 += WIDTH_ELEMENT;
		eyex += WIDTH_ELEMENT * 5/8;
		eyey += HEIGHT_ELEMENT * 3/ 8;
		break;
	}

	//big circle
	sf::CircleShape circle;
	circle.setRadius(WIDTH_ELEMENT/2);
	circle.setFillColor(pacman.getColor());
	circle.setPosition(x, y);
	win.draw(circle);

	//eye 
	circle.setRadius(WIDTH_ELEMENT / 10);
	circle.setFillColor(Color::White);
	circle.setPosition(eyex, eyey);
	win.draw(circle);

	//rectangle
	sf::ConvexShape convex;
	convex.setPointCount(3);
	convex.setPoint(0, sf::Vector2f(x + WIDTH_ELEMENT/2, y + HEIGHT_ELEMENT /2));
	convex.setPoint(1, sf::Vector2f(x1, y1));
	convex.setPoint(2, sf::Vector2f(x2, y2));
	convex.setFillColor(Color::Black);
	win.draw(convex);
}

void drawFood(sf::RenderWindow &win) {
	for(int i = 0; i < foods.size(); i++) {
		sf::RectangleShape rect;
		rect.setSize(sf::Vector2f(WIDTH_ELEMENT / 3, HEIGHT_ELEMENT / 3));
		rect.setPosition(foods[i].getX() * WIDTH_ELEMENT + WIDTH_ELEMENT/3, foods[i].getY()* HEIGHT_ELEMENT + HEIGHT_ELEMENT/3);
		rect.setFillColor(foods[i].getColor());
		win.draw(rect);
	}
}
void drawMap(sf::RenderWindow &win) {
	for(int i = 0; i < maps.size(); i++) {
		sf::RectangleShape rect;
		rect.setSize(sf::Vector2f(WIDTH_ELEMENT, HEIGHT_ELEMENT));
		rect.setPosition(maps[i].getX() * WIDTH_ELEMENT, maps[i].getY()* HEIGHT_ELEMENT);
		rect.setFillColor(maps[i].getColor());
		win.draw(rect);
	}
}

void drawGhosts(sf::RenderWindow &win) {
	for(int i = 0; i < ghosts.size(); i++) {
		int x = ghosts[i].getX() * WIDTH_ELEMENT;
		int y = ghosts[i].getY() * HEIGHT_ELEMENT;
		//big circle
		sf::CircleShape circle;
		circle.setRadius(WIDTH_ELEMENT/2);
		circle.setFillColor(ghosts[i].getColor());
		circle.setPosition(x, y);
		win.draw(circle);

		//rectangle
		sf::RectangleShape rect;
		rect.setFillColor(ghosts[i].getColor());
		rect.setPosition(x, y + HEIGHT_ELEMENT / 2);
		rect.setSize(sf::Vector2f(WIDTH_ELEMENT, HEIGHT_ELEMENT / 2));
		win.draw(rect);
		//eye 
		circle.setRadius(WIDTH_ELEMENT / 8);
		circle.setFillColor(Color::White);
		circle.setPosition(x + WIDTH_ELEMENT/8, y + HEIGHT_ELEMENT *3/8);
		win.draw(circle);

		circle.setPosition(x + WIDTH_ELEMENT * 5/8, y + HEIGHT_ELEMENT *3/8);
		win.draw(circle);
		//clear foot
		rect.setFillColor(Color::Black);
		rect.setPosition(x, y + HEIGHT_ELEMENT * 7/ 8);
		rect.setSize(sf::Vector2f(WIDTH_ELEMENT, HEIGHT_ELEMENT / 8));
		win.draw(rect);

		//4 circle
		circle.setFillColor(ghosts[i].getColor());
		for(int j = -4; j <= 2; j +=2) {
			circle.setRadius(WIDTH_ELEMENT/8);
			circle.setPosition(x + WIDTH_ELEMENT / 2 + j * WIDTH_ELEMENT / 8, y + HEIGHT_ELEMENT * 3/4);
			win.draw(circle);
		}
	}
}

void controlGame(){
	controlObject(pacman, false);
	for(int i = 0; i < ghosts.size(); i++) {
		controlObject(ghosts[i], true);
	}
	controlScore();
}

void controlObject(Character &cha, bool isGhost) {
	vector<Constant::Direction> directions = whereCanGo(cha.getX(), cha.getY());
	if(isContained(directions, cha.getDirection())) {
		if(isContained(directions, opositeOf(cha.getDirection())))
			directions.erase(remove(directions.begin(), directions.end(), opositeOf(cha.getDirection())), directions.end());
	}

	if(isGhost && ceil(cha.getX()) == floor(cha.getX()) && ceil(cha.getY()) == floor(cha.getY())) {
		cha.setDirection(directions[rand() % directions.size()]);
	}

	switch(cha.getDirection()) {
	case Constant::Direction::right:
		if(isContained(directions, Constant::Direction::right)) {
			cha.goRight();
		}
		break;
	case Constant::Direction::left:
		if(isContained(directions, Constant::Direction::left)) {
			cha.goLeft();
		}
		break;
	case Constant::Direction::up:
		if(isContained(directions, Constant::Direction::up)) {
			cha.goUp();
		}
		break;	
	case Constant::Direction::down:
		if(isContained(directions, Constant::Direction::down)) {
			cha.goDown();
		}
		break;
	}
}

vector<Constant::Direction> whereCanGo(float x, float y) {
	vector<Constant::Direction> directions;
	for(int i = 0; i < 4; i++) {
		directions.push_back(static_cast<Constant::Direction>(i));
	}
	if(isCrashed(x + 1, y))
		directions.erase(remove(directions.begin(), directions.end(), Constant::Direction::right), directions.end());
	if(isCrashed(x - 1, y))
		directions.erase(remove(directions.begin(), directions.end(), Constant::Direction::left), directions.end());
	if(isCrashed(x, y - 1))
		directions.erase(remove(directions.begin(), directions.end(), Constant::Direction::up), directions.end());
	if(isCrashed(x, y + 1))
		directions.erase(remove(directions.begin(), directions.end(), Constant::Direction::down), directions.end());
	return directions;
}

bool isCrashed(float x, float y) {
	for(int i = 0; i < maps.size(); i++) {
		if(maps[i].getX() == x && maps[i].getY() == y) {
			return true;
		}
	}
	return false;
}
Constant::Direction opositeOf(Constant::Direction direction) {
	switch(direction) {
	case Constant::Direction::left:
		return Constant::Direction::right;
	case Constant::Direction::right:
		return Constant::Direction::left;
	case Constant::Direction::up:
		return Constant::Direction::down;
	case Constant::Direction::down:
		return Constant::Direction::up;
	}
}
void controlScore(){

}