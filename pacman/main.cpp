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
void drawGhost(sf::RenderWindow &);

void pushToMap(int,int); 
void pushMultipleToMap(int,int); 
bool isContained(vector<Element>, Element);
bool isContained(vector<Character>, Character);

vector<Element> maps;
vector<Element> foods;
vector<Character> ghosts;
//Pacman pacman;

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
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		//   window.draw(shape);
		//	window.draw(rectangle);
		draw(window);
		window.display();
		Sleep(100);
	}

	return 0;
}

void drawPacman(sf::RenderWindow & win) {

}

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
		Character ghost = Character(x, y, COLOR_GHOST);
		if(!isContained(ghosts, ghost))
			ghosts.push_back(ghost);
		else 
			i--;
	}
}
void generatePacman(){

}

void draw(sf::RenderWindow &win) {
	drawMap(win);
	drawFood(win);
	drawGhost(win);
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

void drawGhost(sf::RenderWindow &win) {
	for(int i = 0; i < ghosts.size(); i++) {
		int x = ghosts[i].getX() * WIDTH_ELEMENT;
		int y = ghosts[i].getY() * HEIGHT_ELEMENT;
		sf::CircleShape circle;
		circle.setRadius(WIDTH_ELEMENT/2);
		circle.setFillColor(ghosts[i].getColor());
		circle.setPosition(x, y);
		win.draw(circle);
	}
}
