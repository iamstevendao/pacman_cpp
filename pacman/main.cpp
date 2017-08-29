#include <SFML/Graphics.hpp>
#include "main.h"
#include <sstream>

//global elements
vector<Element> maps;
vector<Element> foods;
vector<Element> cherries;
vector<Character> ghosts;
Pacman pacman;
int score;
bool isMenu;
int currentChoice;

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
{
	RenderWindow window(VideoMode(WIDTH_WINDOW, HEIGHT_WINDOW), "Pacman");
	showMenu();
	generate();
	Font font;
	font.loadFromFile("ARCADECLASSIC.TTF");
	currentChoice = 1;
	//Main Loop
	while (window.isOpen())
	{
		Event event;
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
					if(!isMenu) {
						pacman.setDirection(Constant::Direction::left);
						pacman.setY(pacman.round(pacman.getY()));
					}
					break;
				case Keyboard::Right:
					if(!isMenu) {
						pacman.setDirection(Constant::Direction::right);
						pacman.setY(pacman.round(pacman.getY()));
					}
					break;
				case Keyboard::Up:
					if(!isMenu) {
						pacman.setDirection(Constant::Direction::up);
						pacman.setX(pacman.round(pacman.getX()));
					} else if(isMenu && currentChoice == 2) {
						currentChoice--;
					}
					break;
				case Keyboard::Down:
					if(!isMenu) {
						pacman.setDirection(Constant::Direction::down);
						pacman.setX(pacman.round(pacman.getX()));
					}else if(isMenu && currentChoice == 1) {
						currentChoice++;
					}
					break;
				case Keyboard::Return:
					if(isMenu) {
						if(currentChoice == 1) {
							initialize();
						} else 
							return 0;
					}
					break;
				}
									}
									break;
			default:
				break;
			}
		}

		window.clear();
		draw(window, font);
		if(!isMenu)
			controlGame();
		window.display();
		Sleep(NUMBER_INTERVAL);
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
		return true;
	else
		return false;

}
void initialize() {
	isMenu = false;
	score = 0;
	srand(time(NULL)); 
}
void showMenu() {
	isMenu = true;
}

void generate(){
	generateMap();
	generateFood();
	generateGhost();
	generatePacman();
	generateCherries();
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

void generateCherries(){
	while(cherries.size() < NUMBER_CHERRY) {
		int index = rand() % foods.size();
		Element ele(foods[index].getX(), foods[index].getY(), Color::Red);
		if(!isContained(cherries, ele)) {
			cherries.push_back(ele);
			foods.erase(foods.begin() + index);
		}
	}
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
	for(int i = 0; i < NUMBER_GHOST; i++) {
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

void draw(RenderWindow &win, Font &font) {
	drawMap(win);
	drawFood(win);
	drawCherries(win);
	drawGhosts(win);
	drawPacman(win);
	if(isMenu) {
		drawMenu(win, score, font);
	}
}

void drawMenu(RenderWindow &win, int score, Font &font) {
	RectangleShape rect;
	rect.setFillColor(COLOR_BG);
	rect.setPosition(WIDTH_WINDOW / 4, HEIGHT_WINDOW / 4);
	rect.setSize(Vector2f(WIDTH_WINDOW / 2, HEIGHT_WINDOW / 2));
	win.draw(rect);

	Text text;
	text.setFont(font);
	text.setColor(Color::White);
	text.setCharacterSize(40);

	if(score != 0) {
		ostringstream oss;
		oss << "SCORE  " << score;
		text.setString(oss.str());
		text.setPosition(TEXT_SCORE_X, TEXT_SCORE_Y);
		win.draw(text);
	}

	text.setString("PACMAN");
	text.setPosition(TEXT_PACMAN_X, TEXT_PACMAN_Y);
	win.draw(text);

	text.setString("PLAY");
	text.setPosition(TEXT_PLAY_X, TEXT_PLAY_Y);
	win.draw(text);

	text.setString("EXIT");
	text.setPosition(TEXT_EXIT_X, TEXT_EXIT_Y);
	win.draw(text);

	ConvexShape convex;
	convex.setPointCount(3);
	convex.setFillColor(Color::White);

	int x = currentChoice == 1 ? TEXT_PLAY_X : TEXT_EXIT_X;
	int y = currentChoice == 1 ? TEXT_PLAY_Y : TEXT_EXIT_Y;
	convex.setPoint(0, Vector2f(x - 20, y + 20));
	convex.setPoint(1, Vector2f(x - 10, y + 25));
	convex.setPoint(2, Vector2f(x - 20, y + 30));
	win.draw(convex);

	//credit
	text.setCharacterSize(30);
	text.setString("BY  STEVEN DAO  6326");
	text.setPosition(TEXT_CREDIT_X, TEXT_CREDIT_Y);
	win.draw(text);
}

void drawPacman(RenderWindow &win) {
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
	CircleShape circle;
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
	ConvexShape convex;
	convex.setPointCount(3);
	convex.setPoint(0, Vector2f(x + WIDTH_ELEMENT/2, y + HEIGHT_ELEMENT /2));
	convex.setPoint(1, Vector2f(x1, y1));
	convex.setPoint(2, Vector2f(x2, y2));
	convex.setFillColor(COLOR_BG);

	if(pacman.switchOpen())
		win.draw(convex);
}

void drawCherries(RenderWindow &win) {
	for(int i = 0; i < cherries.size(); i++) {
		int x = cherries[i].getX() * WIDTH_ELEMENT;
		int y = cherries[i].getY() * HEIGHT_ELEMENT;

		//first circle
		CircleShape circle;
		circle.setRadius(WIDTH_ELEMENT/4);
		circle.setFillColor(COLOR_CHERRY);
		circle.setPosition(x, y + HEIGHT_ELEMENT / 4);
		win.draw(circle);

		//second circle
		circle.setPosition(x + WIDTH_ELEMENT / 2, y + HEIGHT_ELEMENT / 2);
		win.draw(circle);

		//branches
		RectangleShape rect;
		rect.setFillColor(COLOR_CHERRY_BRANCH);
		rect.setPosition(x + WIDTH_ELEMENT / 4, y + HEIGHT_ELEMENT * 1 / 8);
		rect.setSize(Vector2f(WIDTH_ELEMENT * 3 / 4, HEIGHT_ELEMENT / 8));
		win.draw(rect);

		rect.setPosition(x + WIDTH_ELEMENT * 3 / 4, y);
		rect.setSize(Vector2f(WIDTH_ELEMENT / 8, HEIGHT_ELEMENT /2));
		win.draw(rect);
	}
}

void drawFood(RenderWindow &win) {
	for(int i = 0; i < foods.size(); i++) {
		RectangleShape rect;
		rect.setSize(Vector2f(WIDTH_ELEMENT / 3, HEIGHT_ELEMENT / 3));
		rect.setPosition(foods[i].getX() * WIDTH_ELEMENT + WIDTH_ELEMENT/3, foods[i].getY()* HEIGHT_ELEMENT + HEIGHT_ELEMENT/3);
		rect.setFillColor(foods[i].getColor());
		win.draw(rect);
	}
}
void drawMap(RenderWindow &win) {
	for(int i = 0; i < maps.size(); i++) {
		RectangleShape rect;
		rect.setSize(Vector2f(WIDTH_ELEMENT, HEIGHT_ELEMENT));
		rect.setPosition(maps[i].getX() * WIDTH_ELEMENT, maps[i].getY()* HEIGHT_ELEMENT);
		rect.setFillColor(maps[i].getColor());
		win.draw(rect);
	}
}

void drawGhosts(RenderWindow &win) {
	for(int i = 0; i < ghosts.size(); i++) {
		int x = ghosts[i].getX() * WIDTH_ELEMENT;
		int y = ghosts[i].getY() * HEIGHT_ELEMENT;
		//big circle
		Color color;
		int pow = pacman.getPower() / 80;
		if(pow < 0 || pow == 1 || pow == 5 || pow == 9 || pow == 13) 
			color = ghosts[i].getColor();
		else 
			color = Color::White;

		CircleShape circle;
		circle.setRadius(WIDTH_ELEMENT/2);
		circle.setFillColor(color);
		circle.setPosition(x, y);
		win.draw(circle);

		//rectangle
		RectangleShape rect;
		rect.setFillColor(color);
		rect.setPosition(x, y + HEIGHT_ELEMENT / 2);
		rect.setSize(Vector2f(WIDTH_ELEMENT, HEIGHT_ELEMENT / 2));
		win.draw(rect);

		//eye 
		circle.setRadius(WIDTH_ELEMENT / 8);
		circle.setFillColor(Color::White);
		circle.setPosition(x + WIDTH_ELEMENT/8, y + HEIGHT_ELEMENT *3/8);
		win.draw(circle);

		circle.setPosition(x + WIDTH_ELEMENT * 5/8, y + HEIGHT_ELEMENT *3/8);
		win.draw(circle);

		//clear foot
		rect.setFillColor(COLOR_BG);
		rect.setPosition(x, y + HEIGHT_ELEMENT * 7/ 8);
		rect.setSize(Vector2f(WIDTH_ELEMENT, HEIGHT_ELEMENT / 8));
		win.draw(rect);

		//4 circle
		circle.setFillColor(color);
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
	if(!isGhost)
		pacman.reducePower();
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
	crashGhost();
	eatCherry();
	eatFood();
}

void reset(){
	showMenu();
	clearVectors();
	generate();
}

void clearVectors() {
	maps.clear();
	foods.clear();
	cherries.clear();
	ghosts.clear();
}

void crashGhost(){
	for(int i = 0; i < ghosts.size(); i++) {
		if((ceil(ghosts[i].getX()) == ceil(pacman.getX()) && 
			ceil(ghosts[i].getY()) == ceil(pacman.getY())) || 
			(floor(ghosts[i].getX()) == floor(pacman.getX()) && 
			floor(ghosts[i].getY()) == floor(pacman.getY()))
			){
				if(pacman.getPower() > 0) {
					ghosts.erase(ghosts.begin() + i);
					score += 5;
				} else {
					reset();
				}
		}
	}
}
void eatCherry(){
	for(int i = 0; i < cherries.size(); i++) {
		if(cherries[i].getX() == pacman.round(pacman.getX()) &&
			cherries[i].getY() == pacman.round(pacman.getY())) {
				cherries.erase(cherries.begin() + i);
				pacman.activatePower();
				score += 5;
				break;
		}
	}
}
void eatFood(){
	for(int i = 0; i < foods.size(); i++) {
		if(foods[i].getX() == pacman.round(pacman.getX()) 
			&& foods[i].getY() == pacman.round(pacman.getY())) {
				foods.erase(foods.begin() + i);
				score++;
				break;
		}
	}
	if(foods.size() == 0)
		reset();
}