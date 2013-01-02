#include <cstdlib>
#include <ctime>

#include "definitions.h"

class Fifteen {
	int gameBoard[BOARD_SIZE][BOARD_SIZE];
	int emptyX;
	int emptyY;

	void moveEmptyLeft();
	void moveEmptyRight();
	void moveEmptyUp();
	void moveEmptyDown();
	void randomizeGameBoard();
public:
	Fifteen();
	~Fifteen();
	
	int getGameBoardNum(int, int);
};