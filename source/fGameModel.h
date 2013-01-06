#pragma once

#include "definitions.h"

class fGameModel {
	int gameBoard[BOARD_SIZE][BOARD_SIZE];
	int emptyX;
	int emptyY;

	void moveEmptyLeft();
	void moveEmptyRight();
	void moveEmptyUp();
	void moveEmptyDown();
	
public:
	fGameModel();
	~fGameModel();
	
	void randomizeGameBoard();
	bool setMove(int, int);
	int getGameBoardNum(int, int);
	bool isOver();

	int getEmptyX();
	int getEmptyY();
};