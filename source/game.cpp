#include "game.h"

Fifteen::Fifteen() {
	int k = 1;
	for (int y = 0; y < BOARD_SIZE; ++y)
		for (int x = 0; x < BOARD_SIZE; ++x)
			gameBoard[x][y] = k++;
	gameBoard[BOARD_SIZE-1][BOARD_SIZE-1] = 0;
}