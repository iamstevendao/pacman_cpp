#include "Pacman.h"
#include "Element.h"
#include "Constant.h"
#include <cstdlib>
#include <Windows.h>
#include <iostream>
#include <math.h>

using namespace std;
using namespace sf;

//generate elements of the game
void generate();
void generateFood();
void generateGhost();
void generatePacman();
void generateMap();
void generateCherries();

//drawing
void drawMenu(RenderWindow &, int score, Font &);
void draw(RenderWindow &, Font &);
void drawMap(RenderWindow &);
void drawFood(RenderWindow &);
void drawPacman(RenderWindow &);
void drawGhosts(RenderWindow &);
void drawCherries(RenderWindow &);

//control game
void controlGame();
void controlObject(Character &, bool);
void controlScore();
void crashGhost();
void eatCherry();
void eatFood();

//functionality
void initialize();
void reset();
void pushToMap(int,int); 
void pushMultipleToMap(int,int); 
bool isContained(vector<Element>, Element);
bool isContained(vector<Character>, Character);
bool isContained(vector<Constant::Direction>, Constant::Direction);
bool isCrashed(float, float);
Constant::Direction opositeOf(Constant::Direction);
vector<Constant::Direction> whereCanGo(float,float);

