#include "fGameModel.h"
#include <cstdlib>
#include <ctime>

fGameModel::fGameModel() {
	int k = 1;
	for (int y = 0; y < BOARD_SIZE; ++y)
		for (int x = 0; x < BOARD_SIZE; ++x)
			gameBoard[x][y] = k++;
	gameBoard[BOARD_SIZE-1][BOARD_SIZE-1] = 0;
	emptyX = emptyY = BOARD_SIZE - 1;
	randomizeGameBoard();
}

fGameModel::~fGameModel() {

}

int fGameModel::getGameBoardNum(int x, int y) {
	return gameBoard[x][y];
}

void fGameModel::moveEmptyLeft() {
	if (emptyX > 0) {
		gameBoard[emptyY][emptyX] = gameBoard[emptyY][emptyX - 1];
		gameBoard[emptyY][emptyX - 1] = 0;
		emptyX--;
	}
}

void fGameModel::moveEmptyRight() {
	if (emptyX < BOARD_SIZE - 1) {
		gameBoard[emptyY][emptyX] = gameBoard[emptyY][emptyX + 1];
		gameBoard[emptyY][emptyX + 1] = 0;
		emptyX++;
	}
}

void fGameModel::moveEmptyUp() {
	if (emptyY > 0) {
		gameBoard[emptyY][emptyX] = gameBoard[emptyY - 1][emptyX];
		gameBoard[emptyY - 1][emptyX] = 0;
		emptyY--;
	}
}

void fGameModel::moveEmptyDown() {
	if (emptyY < BOARD_SIZE - 1) {
		gameBoard[emptyY][emptyX] = gameBoard[emptyY + 1][emptyX];
		gameBoard[emptyY + 1][emptyX] = 0;
		emptyY++;
	}
}

void fGameModel::randomizeGameBoard() {
	srand(time(0));
	for (int i = 0; i < 20000; ++i) {
		int mode = 1 + rand() % 4;
		switch(mode) {
			case 1: moveEmptyUp();    break;
			case 2: moveEmptyDown();  break;
			case 3: moveEmptyLeft();  break;
			case 4: moveEmptyRight(); break;
		}
	}
}