#include <SFML/Graphics.hpp>
#include "main.h"
#include <sstream>

#pragma region Global Variables
vector<Element> maps;
vector<Element> foods;
vector<Element> cherries;
vector<Character> ghosts;
Pacman pacman;
int score;
bool isMenu;
int currentChoice;

#pragma endregion

#pragma region Main

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
{
	RenderWindow window(VideoMode(WIDTH_WINDOW, HEIGHT_WINDOW), "Pacman");
	Font font;
	font.loadFromFile("ARCADECLASSIC.TTF");

	showMenu();
	generate();

	//Main Loop
	while (window.isOpen())
	{
		Event event;
		//check events during game
		while (window.pollEvent(event))
		{
			switch (event.type)
			{

				// window closed
			case Event::Closed:
				window.close();
				break;

				//key pressed event
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
		//redraw window
		window.clear();
		draw(window, font);

		//run controller
		if(!isMenu)
			controlGame();
		window.display();

		//stop frame
		Sleep(NUMBER_INTERVAL);
	}

	return 0;
}

#pragma endregion

#pragma region Game Setup

void initialize() {
	isMenu = false;
	score = 0;
	srand(time(NULL)); 
}

void showMenu() {
	currentChoice = 1;
	isMenu = true;
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

#pragma endregion

#pragma region Generate Game
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

		Character ghost = Character(x, y, Constant::GhostColors(color), i);
		if(!isContained(ghosts, ghost)){
			ghost.setTarget(generateTarget());
			ghosts.push_back(ghost);
		}
		else 
			i--;
	}
}
void generatePacman(){
	pacman = Pacman(1,1, COLOR_PACMAN);
	pacman.setDirection(Constant::Direction::right);
}

int generateTarget(){
	if(cherries.size() > 0) 
		return rand() % NUMBER_GHOST > NUMBER_GHOST / 4 ? - 1 : rand() % cherries.size();
	return -1;
}

#pragma endregion 

#pragma region Draw Game
void draw(RenderWindow &win, Font &font) {
	drawMaps(win);
	drawFoods(win);
	drawCherries(win);
	drawGhosts(win);
	drawPacman(win);
	if(isMenu) {
		drawMenu(win, score, font);
	}
	//drawPath(win);
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

	//body
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

	//mouth
	ConvexShape convex;
	convex.setPointCount(3);
	convex.setPoint(0, Vector2f(x + WIDTH_ELEMENT/2, y + HEIGHT_ELEMENT /2));
	convex.setPoint(1, Vector2f(x1, y1));
	convex.setPoint(2, Vector2f(x2, y2));
	convex.setFillColor(COLOR_BG);

	if(pacman.toggleOpen())
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

void drawFoods(RenderWindow &win) {
	for(int i = 0; i < foods.size(); i++) {
		RectangleShape rect;
		rect.setSize(Vector2f(WIDTH_ELEMENT / 3, HEIGHT_ELEMENT / 3));
		rect.setPosition(foods[i].getX() * WIDTH_ELEMENT + WIDTH_ELEMENT/3, foods[i].getY()* HEIGHT_ELEMENT + HEIGHT_ELEMENT/3);
		rect.setFillColor(foods[i].getColor());
		win.draw(rect);
	}
}
void drawMaps(RenderWindow &win) {
	for(int i = 0; i < maps.size(); i++) {
		RectangleShape rect;
		rect.setSize(Vector2f(WIDTH_ELEMENT, HEIGHT_ELEMENT));
		rect.setPosition(maps[i].getX() * WIDTH_ELEMENT, maps[i].getY()* HEIGHT_ELEMENT);
		rect.setFillColor(maps[i].getColor());
		win.draw(rect);
	}
}

void drawPath(RenderWindow &win) {
	if(pacman.getPower() < 0) {
		for(int i = 0; i < ghosts.size(); i++) {
			Path* current = ghosts[i].getPath();
			while(current->next) {
				current = current->next;
				RectangleShape rect;
				rect.setSize(Vector2f(WIDTH_ELEMENT / 3, HEIGHT_ELEMENT / 3));
				rect.setPosition(current->point.x * WIDTH_ELEMENT + WIDTH_ELEMENT/3, current->point.y* HEIGHT_ELEMENT + HEIGHT_ELEMENT/3);
				rect.setFillColor(ghosts[i].getColor());
				win.draw(rect);
			}
		}
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
#pragma endregion

#pragma region Control Game

void controlGame(){
	controlObject(pacman, false);
	controlPath();
	for(int i = 0; i < ghosts.size(); i++) {
		controlObject(ghosts[i], true);
	}
	controlScore();
}

void controlPath() {
	for(int i = 0; i < ghosts.size(); i++) {
		ghosts[i].updateHead();
		Point destination;
		Path* departure = ghosts[i].getPath(); 
		if(ghosts[i].getTarget() == -1) {
			destination = Point(pacman.round(pacman.getX()), pacman.round(pacman.getY()));
		} else {
			if(ghosts[i].getTarget() >= cherries.size() || !reachCherry(departure)) {
				ghosts[i].setTarget(rand() % cherries.size());
			}
			destination = Point(cherries[ghosts[i].getTarget()].getX(), cherries[ghosts[i].getTarget()].getY());
		}
		ghosts[i].setPath(findPath(i, departure, destination));
	}
}

bool reachCherry(Path* ghost) {
	for(int i = 0; i < cherries.size(); i++) {
		if(ghost->point.x == cherries[i].getX() && ghost->point.y == cherries[i].getY()) {
			return true;
		}
	}
	return false;
}

Path* findPath(int ind, Path* departure, Point arrival) {
	Point dep = Point(floor(departure->point.x), floor(departure->point.y));
	if(arrival.x == dep.x && arrival.y == dep.y) {
		return NULL;
	}
	vector<Path*> queue;
	queue.push_back(departure);
	int index = 0;
	Path *result = NULL;
	while(!result) {
		vector<Point> adj = getAdjacences(ind, queue, queue[index]->point);
		for(int i = 0; i < adj.size(); i++) {
			Path *path = new Path();
			path->point = adj[i];
			path->next = queue[index];
			queue.push_back(path);
			if(adj[i].x == arrival.x && adj[i].y == arrival.y)
				result = path;
		}
		index++;
	}

	//reverse the linked list
	Path * curr = result, *next = NULL, *prev = NULL;
	while(curr) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	return prev->next;
}

vector<Point> getAdjacences(int ind, vector<Path*> queue, Point point) {
	vector<Point> adj;
	adj.push_back(Point(point.x, point.y - 1));
	adj.push_back(Point(point.x, point.y + 1));
	adj.push_back(Point(point.x - 1, point.y));
	adj.push_back(Point(point.x + 1, point.y));
	adj = shuffle(ind, adj);
	for(int i = 0; i < adj.size(); i++) {
		if(adj[i].x < 1 || adj[i].y < 1 || 
			adj[i].x > SIZE_GRID || adj[i].y > SIZE_GRID ||
			isInMap(adj[i]) || isInQueue(queue, adj[i])) {
				adj.erase(adj.begin() + i);
				i--;
		}
	}
	return adj;
}

bool isInMap(Point point) {
	for(int i = 0; i < maps.size(); i++) {
		if(point.x == maps[i].getX() && point.y == maps[i].getY()) {
			return true;
		}
	}
	return false;
}

bool isInQueue(vector<Path*> queue, Point point) {
	for(int i = 0; i < queue.size(); i++) {
		if(point.x == queue[i]->point.x && point.y == queue[i]->point.y)
			return true;
	}
	return false;
}

vector<Point> shuffle(int ind, vector<Point> points) {
	vector<Point> ret;
	int index = ind % 4;
	for(int i = 0; i < 4; i++) {
		ret.push_back(points[(index + i) % 4]);
	}
	return ret;
}

void controlObject(Character &cha, bool isGhost) {
	//get all directions ghost can go
	vector<Constant::Direction> directions = whereCanGo(cha.getX(), cha.getY());
	if(isGhost) {

		//generate a new target after an amount of time
		if(pacman.getPower() % (NUMBER_INTERVAL * NUMBER_POWER * 2) == 0) {
			cha.setTarget(generateTarget());
		}

		//when pacman activates power, go backwards
		if (pacman.getPower() >= NUMBER_INTERVAL * (NUMBER_POWER - 1)) {
			cha.setDirection(opositeOf(cha.getDirection()));
		} else {

			if(isContained(directions, cha.getDirection())) {
				//remove oposite direction (keep ghost from suddenly reverse its direction
				if(isContained(directions, opositeOf(cha.getDirection())))
					directions.erase(remove(directions.begin(), directions.end(), opositeOf(cha.getDirection())), directions.end());
			}

			if(ceil(cha.getX()) == floor(cha.getX()) && ceil(cha.getY()) == floor(cha.getY())) {
				if(pacman.getPower() > 0)
					//if pacman is having its power, random direction
					cha.setDirection(directions[rand() % directions.size()]);
				else //otherwise follow up what it is up to
					cha.followPath();
			}
		}
	}
	//reduce power of pacman
	else
		pacman.reducePower();

	//move
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

void controlScore(){
	crashGhost();
	eatCherry();
	eatFood();
}

void crashGhost(){
	for(int i = 0; i < ghosts.size(); i++) {
		if((ceil(ghosts[i].getX()) == ceil(pacman.getX()) && 
			ceil(ghosts[i].getY()) == ceil(pacman.getY())) || 
			(floor(ghosts[i].getX()) == floor(pacman.getX()) && 
			floor(ghosts[i].getY()) == floor(pacman.getY()))){
				if(pacman.getPower() > 0) {
					ghosts.erase(ghosts.begin() + i);
					score += 5;
					break;
				} else {
					reset();
				}
		}
	}

	//win when there is no more ghosts
	if(ghosts.size() == 0)
		reset();
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

	//win when there is no more food
	if(foods.size() == 0)
		reset();
}

#pragma endregion

#pragma region Utils  

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

#pragma endregion

