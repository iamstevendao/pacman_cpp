#define CHARACTER_WIDTH 100
#define CHARACTER_HEIGHT 100
class Character {
private:
	int x;
	int y;
public:
	int getX();
	int getY();
	void goLeft();
	void goRight();
	void goUp();
	void goDown();
};