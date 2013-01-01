#include "definitions.h"

class Fifteen {
	int gameBoard[BOARD_SIZE][BOARD_SIZE];
public:
	Fifteen();
	~Fifteen();
	
	int getGameBoardNum(int, int);
};