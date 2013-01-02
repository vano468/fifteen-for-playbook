#ifndef GAME_H
#define GAME_H

#include "definitions.h"

class Fifteen {
	int gameBoard[BOARD_SIZE][BOARD_SIZE];
	int emptyX;
	int emptyY;
	int state;

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

#endif //GAME_H